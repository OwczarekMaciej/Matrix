#include "Matrix.h"

Matrix::Matrix()
{
    mtx_ptr = nullptr;
}

Matrix::Matrix(unsigned int rows, unsigned int comlumns)
{
    rcmatrix *temp = new rcmatrix(rows, comlumns);
    mtx_ptr = temp;
}

Matrix::~Matrix()
{
    if (--mtx_ptr->refcount == 0)
        delete mtx_ptr;
    else
    {
        mtx_ptr = nullptr;
    }
}

Matrix::Matrix(const Matrix &source)
{
    source.mtx_ptr->refcount++;
    mtx_ptr = source.mtx_ptr;
}

Matrix &Matrix::operator=(const Matrix &rhs)
{
    if (this != &rhs)
    {
        rhs.mtx_ptr->refcount++;
        if (--mtx_ptr->refcount == 0)
            delete mtx_ptr;
        mtx_ptr = rhs.mtx_ptr;
    }
    return *this;
}

Matrix::rcmatrix::rcmatrix(unsigned int rows, unsigned int columns)
    : rows(rows), columns(columns)
{
    refcount = 1;
    data = new double *[rows]{};
    for (unsigned int i = 0; i < rows; i++)
    {
        data[i] = new double[columns]{};
    }
}

Matrix::rcmatrix::~rcmatrix()
{
    for (unsigned int i = 0; i < rows; i++)
        delete[] data[i];
    delete[] data;
}

Matrix::rcmatrix *Matrix::rcmatrix::detach()
{
    if (refcount == 1)
        return this;
    rcmatrix *temp = new rcmatrix(rows, columns);
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
            temp->data[i][j] = data[i][j];
    }
    refcount--;
    return temp;
}

std::ostream &operator<<(std::ostream &os, const Matrix &rhs)
{
    if (rhs.mtx_ptr == nullptr)
        return os << "Matrix is empty" << std::endl;
    for (unsigned int i = 0; i < rhs.mtx_ptr->rows; i++)
    {
        for (unsigned int j = 0; j < rhs.mtx_ptr->columns; j++)
            os << rhs.mtx_ptr->data[i][j] << "\t";
        os << std::endl;
    }
    return os;
}

bool Matrix::areMtxEven(const Matrix &rhs) const
{
    return (mtx_ptr->columns == rhs.mtx_ptr->columns && mtx_ptr->rows == rhs.mtx_ptr->rows);
}

Matrix &Matrix::operator+=(const Matrix &rhs)
{
    if (this->areMtxEven(rhs))
    {
        mtx_ptr = mtx_ptr->detach();
        for (unsigned int i = 0; i < mtx_ptr->rows; i++)
            for (unsigned int j = 0; j < mtx_ptr->columns; j++)
                mtx_ptr->data[i][j] += rhs.mtx_ptr->data[i][j];
    }
    else
    {
        throw IllegalMatrixDiemensions();
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &rhs)
{

    if (this->areMtxEven(rhs))
    {
        mtx_ptr = mtx_ptr->detach();
        for (unsigned int i = 0; i < mtx_ptr->rows; i++)
            for (unsigned int j = 0; j < mtx_ptr->columns; j++)
                mtx_ptr->data[i][j] -= rhs.mtx_ptr->data[i][j];
    }
    else
    {
        throw IllegalMatrixDiemensions();
    }

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &rhs)
{
    if (mtx_ptr->columns == rhs.mtx_ptr->rows)
    {
        rcmatrix *temp = new rcmatrix(mtx_ptr->rows, rhs.mtx_ptr->columns);
        for (unsigned int i = 0; i < mtx_ptr->rows; ++i)
            for (unsigned int j = 0; j < rhs.mtx_ptr->columns; ++j)
            {
                double sum = 0.0;
                for (unsigned int k = 0; k < mtx_ptr->columns; ++k)
                {
                    sum += mtx_ptr->data[i][k] * rhs.mtx_ptr->data[k][j];
                }
                temp->data[i][j] = sum;
            }
        if (--mtx_ptr->refcount == 0)
            delete mtx_ptr;
        mtx_ptr = temp;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &rhs) const
{
    return Matrix(*this) += rhs;
}

Matrix Matrix::operator-(const Matrix &rhs) const
{
    return Matrix(*this) -= rhs;
}
Matrix Matrix::operator*(const Matrix &rhs) const
{
    return Matrix(*this) *= rhs;
}

bool Matrix::operator==(const Matrix &rhs) const
{
    if (this->areMtxEven(rhs))
    {
        for (unsigned int i = 0; i < mtx_ptr->rows; i++)
            for (unsigned int j = 0; j < mtx_ptr->columns; j++)
                if (mtx_ptr->data[i][j] != rhs.mtx_ptr->data[i][j])
                    return false;
        return true;
    }
    else
        throw IllegalMatrixDiemensions();
    return false;
}

bool Matrix::operator!=(const Matrix &rhs) const
{
    if (this->areMtxEven(rhs))
    {
        for (unsigned int i = 0; i < mtx_ptr->rows; i++)
            for (unsigned int j = 0; j < mtx_ptr->columns; j++)
                if (mtx_ptr->data[i][j] != rhs.mtx_ptr->data[i][j])
                    return true;
        return false;
    }
    else
        throw IllegalMatrixDiemensions();
    return true;
}
Matrix::Mref Matrix::operator()(unsigned int row, unsigned int column)
{

    if (mtx_ptr->columns - 1 < column || mtx_ptr->rows - 1 < row)
    {
        throw IllegalMatrixDiemensions();
    }
    return Mref(*this, column, row);
}

double Matrix::operator()(unsigned int column, unsigned int row) const
{
    return Mref(*this, column, row);
}

Matrix::Mref::operator double() const
{
    return matrix.mtx_ptr->data[rowno][colno];
}

Matrix::Mref &Matrix::Mref::operator=(double d)
{
    matrix.mtx_ptr->data[rowno][colno] = d;
    return *this;
}

Matrix::Mref &Matrix::Mref::operator=(const Mref &ref)
{
    return operator=((double)ref);
}

std::istream &operator>>(std::istream &is, Matrix &rhs)
{
    unsigned int col, row;
    if (!(is >> row) || !(is >> col))
    {
        throw IllegalInput();
    }
    Matrix::rcmatrix *temp;
    temp = new Matrix::rcmatrix(row, col);
    for (unsigned int i = 0; i < row; i++)
        for (unsigned int j = 0; j < col; j++)
        {
            if (!(is >> temp->data[i][j]))
            {
                throw IllegalInput();
            }
        }
    rhs.mtx_ptr = temp;
    return is;
}
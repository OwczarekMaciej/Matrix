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
    mtx_ptr->refcount--;
    if (mtx_ptr->refcount == 0)
        delete mtx_ptr;
    else
        mtx_ptr = nullptr;
}

Matrix::Matrix(const Matrix &source)
{
    source.mtx_ptr->refcount++;
    mtx_ptr = source.mtx_ptr;
}
Matrix &Matrix::operator=(const Matrix &rhs)
{
    rhs.mtx_ptr->refcount++;
    if (--mtx_ptr->refcount == 0)
        delete mtx_ptr;
    mtx_ptr = rhs.mtx_ptr;
    return *this;
}

Matrix::rcmatrix::rcmatrix(unsigned int rows, unsigned int columns)
    : rows(rows), columns(columns)
{
    refcount = 1;
    try
    {
        data = new double *[rows];
        for (unsigned int i = 0; i < rows; i++)
        {
            try
            {
                data[i] = new double[columns];
            }
            catch (const MemoryAllocFailed &e)
            {
                std::cerr << e.what() << '\n';
                abort();
            }
        }
    }
    catch (const MemoryAllocFailed &e)
    {
        std::cerr << e.what() << '\n';
        abort();
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
    os << rhs.mtx_ptr->refcount << std::endl;
    return os;
}

bool Matrix::areMtxEven(const Matrix &rhs) const
{
    return (mtx_ptr->columns == rhs.mtx_ptr->columns && mtx_ptr->rows == rhs.mtx_ptr->rows);
}

Matrix &Matrix::operator+=(const Matrix &rhs)
{
    try
    {
        if (this->areMtxEven(rhs))
        {
            rcmatrix *temp = new rcmatrix(mtx_ptr->rows, mtx_ptr->columns);
            for (unsigned int i = 0; i < mtx_ptr->rows; i++)
                for (unsigned int j = 0; j < mtx_ptr->columns; j++)
                    temp->data[i][j] = mtx_ptr->data[i][j] + rhs.mtx_ptr->data[i][j];
            if(--mtx_ptr->refcount == 0)
                delete mtx_ptr;
            mtx_ptr = temp;
        }
        else
            throw IllegalMatrixDiemensions();
    }
    catch (const IllegalMatrixDiemensions &e)
    {
        std::cerr << e.what() << '\n';
        abort();
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &rhs)
{
    try
    {
        if (this->areMtxEven(rhs))
        {
            rcmatrix *temp = new rcmatrix(mtx_ptr->rows, mtx_ptr->columns);
            for (unsigned int i = 0; i < mtx_ptr->rows; i++)
                for (unsigned int j = 0; j < mtx_ptr->columns; j++)
                    temp->data[i][j] = mtx_ptr->data[i][j] - rhs.mtx_ptr->data[i][j];
            if(--mtx_ptr->refcount == 0)
                delete mtx_ptr;
            mtx_ptr = temp;
        }
        else
            throw IllegalMatrixDiemensions();
    }
    catch (const IllegalMatrixDiemensions &e)
    {
        std::cerr << e.what() << '\n';
        abort();
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

bool Matrix::operator==(const Matrix &rhs) const
{
    if (this->areMtxEven(rhs))
    {
        for (unsigned int i = 0; i < mtx_ptr->rows; i++)
                for (unsigned int j = 0; j < mtx_ptr->columns; j++)
                    if(mtx_ptr->data[i][j] != rhs.mtx_ptr->data[i][j])
                        return false;
        return true;
    }
    return false;
}

bool Matrix::operator!=(const Matrix &rhs) const
{
    if (this->areMtxEven(rhs))
    {
        for (unsigned int i = 0; i < mtx_ptr->rows; i++)
                for (unsigned int j = 0; j < mtx_ptr->columns; j++)
                    if(mtx_ptr->data[i][j] != rhs.mtx_ptr->data[i][j])
                        return true;
        return false;
    }
    return true;
}
#include "Matrix.h"

Matrix::Matrix()
{
    data = nullptr;
}

Matrix::Matrix(unsigned int rows, unsigned int comlumns)
{
    rcmatrix *temp = new rcmatrix(rows, comlumns);
    data = temp;
}

Matrix::~Matrix()
{
    data->refcount--;
    if(data->refcount == 0)
        delete data;
    else
        data = nullptr;
}

Matrix::Matrix(const Matrix &source)
{
    source.data->refcount++;
    data = source.data;
}

Matrix::rcmatrix::rcmatrix(unsigned int rows, unsigned int columns)
    : rows(rows), columns(columns)
{
    refcount = 1;
    try
    {
        mtx_data = new double *[rows];
        for (int i = 0; i < rows; i++)
        {
            try
            {
                mtx_data[i] = new double[columns];
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
    for (int i = 0; i < rows; i++)
        delete[] mtx_data[i];
    delete[] mtx_data;
}

Matrix::rcmatrix* Matrix::rcmatrix::detach()
{
    if(refcount = 1)
        return this;
    rcmatrix* temp = new rcmatrix(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        temp->mtx_data[i][j] = mtx_data[i][j];
    }
    refcount--;
    return temp;
}
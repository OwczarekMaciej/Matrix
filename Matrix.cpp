#include "Matrix.h"

Matrix::Matrix()
{
    
}

Matrix::~Matrix()
{
}

Matrix::rcmatrix::rcmatrix(unsigned int rows, unsigned int columns)
    : rows(rows), columns(columns)
{
    refcount = 1;
    try
    {
        data = new double *[rows];
        for (int i = 0; i < rows; i++)
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
    for (int i = 0; i < rows; i++)
        delete[] data[i];
    delete[] data;
}

Matrix::rcmatrix* Matrix::rcmatrix::detach()
{
    if(refcount = 1)
        return this;
    rcmatrix* temp = new rcmatrix(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        temp->data[i][j] = data[i][j];
    }
    refcount--;
    return temp;
}
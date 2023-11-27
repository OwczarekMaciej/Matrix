#ifndef MATRIX_H
#define MATRIX_H

#include "IllegalInput.h"
#include "MemoryAllocFailed.h"
#include "IllegalMatrixDiemensions.h"
#include <iostream>

class Matrix
{
    struct rcmatrix;
    rcmatrix *data;
public:
    Matrix();
    ~Matrix();

private:
};

struct Matrix::rcmatrix
{
    double **data;
    unsigned int refcount;
    unsigned int rows;
    unsigned int columns;

    rcmatrix(unsigned int rows = 0, unsigned int columns = 0);
    ~rcmatrix();
    rcmatrix *detach();
};
#endif
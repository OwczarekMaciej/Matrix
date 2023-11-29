#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "IllegalInput.h"
#include "MemoryAllocFailed.h"
#include "IllegalMatrixDiemensions.h"

class Matrix
{
    friend std::ostream &operator<<(std::ostream &os, const Matrix &rhs);

    struct rcmatrix;
    rcmatrix *mtx_ptr;
public:
    Matrix();
    Matrix(unsigned int rows, unsigned int comlumns);
    ~Matrix();
    Matrix(const Matrix &source);
    Matrix &operator+=(const Matrix &rhs);
    Matrix &operator-=(const Matrix &rhs);
    Matrix &operator*=(const Matrix &rhs);
    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;

    bool operator==(const Matrix &rhs) const;
    bool operator!=(const Matrix &rhs) const;

    bool areMtxEven(const Matrix &rhs) const;
};

struct Matrix::rcmatrix
{
    double **data;
    unsigned int refcount;
    unsigned int rows;
    unsigned int columns;

    rcmatrix(unsigned int rows, unsigned int columns);
    ~rcmatrix();
    rcmatrix *detach();
};
#endif
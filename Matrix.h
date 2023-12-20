#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <sstream> 
#include <string>
#include "IllegalInput.h"
#include "MemoryAllocFailed.h"
#include "IllegalMatrixDiemensions.h"

class Matrix
{
    friend std::ostream &operator<<(std::ostream &os, const Matrix &rhs);
    friend std::istream &operator>>(std::istream &os, Matrix &rhs);

    struct rcmatrix;
    rcmatrix *mtx_ptr;
    class Mref;
    bool areMtxEven(const Matrix &rhs) const;

public:
    Matrix();
    Matrix(unsigned int rows, unsigned int comlumns);
    ~Matrix();
    Matrix(const Matrix &source);
    Matrix &operator=(const Matrix &rhs);
    Matrix &operator+=(const Matrix &rhs);
    Matrix &operator-=(const Matrix &rhs);
    Matrix &operator*=(const Matrix &rhs);
    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;
    Matrix operator*(const Matrix &rhs) const;

    bool operator==(const Matrix &rhs) const;
    bool operator!=(const Matrix &rhs) const;


    Mref operator()(unsigned int x, unsigned int y);
    double operator()(unsigned int x, unsigned int y) const;
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

class Matrix::Mref
{
    friend class Matrix;
    const Matrix &matrix;
    unsigned int colno, rowno;
    Mref(const Matrix &mtx, unsigned int col, unsigned int row)
        : matrix(mtx), colno(col), rowno(row){};

public:
    operator double() const;
    Matrix::Mref &operator=(double d);
    Matrix::Mref &operator=(const Mref &ref);
};
#endif
#pragma once
#include "Mytypedef.hpp"
#include "Inspirer.hpp"
class Matrix
{
protected:
    int n;
    int m;
    DT *data;

public:
    Matrix(int _n, int _m);
    Matrix(const Matrix &);
    DT *operator[](int index);
    Matrix T();
    void inspire(const Inspirer &);
    Matrix &operator=(const Matrix &);
    Matrix operator+(const Matrix &) const;
    Matrix operator-(const Matrix &) const;
    Matrix operator*(const Matrix &) const;
    Matrix &operator+=(const Matrix &);
    Matrix &operator-=(const Matrix &);
    Matrix &operator*=(const Matrix &);
};
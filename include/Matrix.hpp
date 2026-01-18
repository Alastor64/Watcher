#pragma once
#include "Mytypedef.hpp"
#include "Inspirer.hpp"
class Matrix
{
protected:
    int n;
    int m;
    DataType *data;
    static Matrix add(Matrix &&a, const Matrix &b);
    static Matrix neg(Matrix &&a);

public:
    Matrix(const Matrix &);
    Matrix(Matrix &&);
    Matrix(int _n, int _m);
    virtual ~Matrix();
    const int width() const;
    const int height() const;
    DataType *operator[](int index) const;
    DataType &operator()(int index) const;
    DataType &operator()(int index1, int index2) const;
    Matrix &operator=(const Matrix &) &;
    Matrix &operator=(Matrix &&) &;
    friend Matrix operator+(const Matrix &, const Matrix &);
    friend Matrix operator+(Matrix &&, const Matrix &);
    friend Matrix operator+(const Matrix &, Matrix &&);
    friend Matrix operator+(Matrix &&, Matrix &&);
    Matrix operator+() const;
    Matrix &operator+=(const Matrix &) &;
    friend Matrix operator-(const Matrix &, const Matrix &);
    Matrix operator-() const;
    Matrix &operator-=(const Matrix &) &;
    Matrix operator*(const Matrix &) const;
    Matrix &operator*=(const Matrix &) &;
    friend std::istream &operator>>(std::istream &, Matrix &);
    friend std::ostream &operator<<(std::ostream &, Matrix &);
    Matrix T() const;
    void inspire(const Inspirer &);
    static Matrix identity(int size);
    static Matrix scalar(int size, const DataType value);
};
#pragma once
#include "Backup.hpp"
#include "Mytypedef.hpp"
#include "Inspirer.hpp"
// template <class T>
// class Backup;
// template <class T>
// class Backup;
class Matrix
{
    friend void Backup<Matrix>::write(const Matrix *data, fstream &fio);
    friend void Backup<Matrix>::read(Matrix *data, fstream &fio);

protected:
    int n;
    int m;
    DataType *data;
    static Matrix add(Matrix &&a, const Matrix &b);
    // void Backup_write(std::fstream &fio);
public:
    Matrix();
    Matrix(const Matrix &);
    Matrix(Matrix &&);
    Matrix(int _n, int _m);
    virtual ~Matrix();
    // friend void Backup<Matrix>::write();
    const int width() const;
    const int height() const;
    DataType *operator[](int index) const;
    DataType &operator()(int index) const;
    DataType &operator()(int index1, int index2) const;
    Matrix &operator=(const Matrix &) &;
    Matrix &operator=(Matrix &&) &;
    Matrix operator+(const Matrix &) &&;
    Matrix operator+(Matrix) &;
    friend Matrix operator+(Matrix a);
    Matrix &operator+=(const Matrix &) &;
    Matrix operator-(const Matrix &) &&;
    Matrix operator-(Matrix) &;
    friend Matrix operator-(Matrix a);
    Matrix &operator-=(const Matrix &) &;
    Matrix operator*(const Matrix &) const;
    Matrix &operator*=(const Matrix &) &;
    friend std::istream &operator>>(std::istream &, Matrix &);
    friend std::ostream &operator<<(std::ostream &, const Matrix &);
    Matrix T() const;
    void inspire(const Inspirer &);
    static Matrix identity(int size);
    static Matrix scalar(int size, const DataType value);
};

// class TestType
// {
//     friend void Backup<TestType>::write(const TestType &data, fstream &fio);
//     friend void Backup<TestType>::read(TestType &data, fstream &fio);

// public:
//     Matrix a;
//     Matrix b;
//     Matrix c;
// };
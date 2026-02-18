#include "Matrix.hpp"
// protected
Matrix Matrix::add(Matrix &&a, const Matrix &b)
{
    if (a.n != b.n || a.m != b.m)
        throw "invailed matrix addition for unequal size";
    for (int i = 0; i < a.n * b.m; i++)
    {
        a.data[i] += b.data[i];
    }
    return move(a);
}
// void Matrix::Backup_write(std::fstream &fio)
// {
// }
// public:
Matrix::Matrix()
{
    data = nullptr;
}
Matrix::Matrix(const Matrix &x)
{
    // cout << "execute copy construct\n"; // #
    if (!x.data)
    {
        data = nullptr;
        return;
    }
    n = x.n;
    m = x.m;
    data = new DataType[n * m];
    for (int i = 0; i < n * m; i++)
        data[i] = x.data[i];
}
Matrix::Matrix(Matrix &&x)
{
    // cout << "execute move construct\n"; // #
    n = x.n;
    m = x.m;
    data = x.data;
    x.data = nullptr;
}
Matrix::Matrix(int _n, int _m) : n(_n), m(_m)
{
    if (!n || !m)
    {
        data = nullptr;
        return;
    }
    // cout << "execute construct\n"; // #
    data = new DataType[n * m];
    for (int i = 0; i < n * m; i++)
        data[i] = 0;
}
Matrix::~Matrix()
{
    delete[] data;
}
const int Matrix::width() const
{
    return m;
}
const int Matrix::height() const
{
    return n;
}
DataType *Matrix::operator[](int index) const
{
    return data + index * m;
}
DataType &Matrix::operator()(int index) const
{
    if (n != 1 && m != 1)
        throw "invalid index for non-vector matrix";
    return data[index];
}
DataType &Matrix::operator()(int index1, int index2) const
{
    return data[index1 * m + index2];
}
Matrix &Matrix::operator=(const Matrix &x) &
{
    // cout << "excute =\n"; // #
    if (data != x.data)
    {
        if (!x.data)
        {
            delete[] data;
            data = nullptr;
            return *this;
        }
        if (n * m != x.n * x.m)
        {
            delete[] data;
            data = new DataType[x.n * x.m];
        }
        n = x.n;
        m = x.m;
        for (int i = 0; i < n * m; i++)
            data[i] = x.data[i];
    }
    return *this;
}
Matrix &Matrix::operator=(Matrix &&x) &
{
    // cout << "excute move=\n"; // #
    if (data != x.data)
    {
        n = x.n;
        m = x.m;
        delete[] data;
        data = x.data;
        x.data = nullptr;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &b) &&
{
    return add(move(*this), b);
}
Matrix Matrix::operator+(Matrix b) &
{
    return add(move(b), *this);
}
Matrix operator+(Matrix a)
{
    return move(a);
}
Matrix &Matrix::operator+=(const Matrix &x) &
{
    return *this = move(*this) + x;
}
Matrix Matrix::operator-(const Matrix &b) &&
{
    if (n != b.n || m != b.m)
        throw "invailed matrix minus for unequal size";
    for (int i = 0; i < n * m; i++)
    {
        data[i] += b.data[i];
    }
    return move(*this);
}
Matrix Matrix::operator-(Matrix b) &
{
    if (n != b.n || m != b.m)
        throw "invailed matrix minus for unequal size";
    for (int i = 0; i < b.n * b.m; i++)
    {
        b.data[i] = data[i] - b.data[i];
    }
    return move(b);
}
Matrix operator-(Matrix a)
{
    for (int i = 0; i < a.n * a.m; i++)
        a.data[i] = -a.data[i];
    return move(a);
}
Matrix &Matrix::operator-=(const Matrix &x) &
{
    return *this = move(*this) - x;
}
Matrix Matrix::operator*(const Matrix &x) const
{
    if (m != x.n)
        throw "invalid matrix multiply for unequal width and height";
    Matrix tmp(n, x.m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < x.m; j++)
        {
            for (int k = 0; k < m; k++)
            {
                tmp(i, j) += this->operator()(i, k) * x[k][j];
            }
        }
    }
    return move(tmp);
}
Matrix &Matrix::operator*=(const Matrix &x) &
{
    return *this = *this * x;
}
std::istream &operator>>(std::istream &input, Matrix &x)
{
    for (int i = 0; i < x.n * x.m; i++)
        input >> x.data[i];
    return input;
}
std::ostream &operator<<(std::ostream &output, Matrix &x)
{
    for (int i = 0; i < x.n; i++)
    {
        for (int j = 0; j < x.m; j++)
        {
            output << x.data[i * x.m + j] << " ";
        }
        output << "\n";
    }
    return output;
}
Matrix Matrix::T() const
{
    Matrix tmp(m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tmp.data[i * n + j] = data[j * m + i];
        }
    }
    return move(tmp);
}
void Matrix::inspire(const Inspirer &x)
{
    for (int i = 0; i < n * m; i++)
        data[i] = x.f(data[i]);
}
Matrix Matrix::identity(int size)
{
    return move(scalar(size, 1));
}
Matrix Matrix::scalar(int size, const DataType value)
{
    Matrix tmp(size, size);
    for (int i = 0; i < size; i++)
        tmp.data[i * size + i] = value;
    return move(tmp);
}
#include "Backup.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
template <>
void Backup<Matrix>::write(const Matrix *data, fstream &fio)
{
    if (data->data)
    {
        fio.write(reinterpret_cast<const char *>(&data->n), sizeof(data->n));
        fio.write(reinterpret_cast<const char *>(&data->m), sizeof(data->m));
        fio.write(reinterpret_cast<const char *>(data->data), data->n * data->m * sizeof(DataType));
    }
    else
    {
        int tmp = 0;
        fio.write(reinterpret_cast<const char *>(&tmp), sizeof(int));
        fio.write(reinterpret_cast<const char *>(&tmp), sizeof(int));
    }
    fio.flush();
}
template <>
void Backup<Matrix>::read(Matrix *data, fstream &fio)
{
    int n, m;
    fio.read(reinterpret_cast<char *>(&n), sizeof(n));
    fio.read(reinterpret_cast<char *>(&m), sizeof(m));
    Matrix tmp(n, m);
    if (tmp.data)
        fio.read(reinterpret_cast<char *>(tmp.data), n * m * sizeof(DataType));
    *data = move(tmp);
}
// template <>
// void Backup<Vector<Matrix>>::write(const Vector<Matrix> *data, fstream &fio) {}
// template <>
// void Backup<Vector<Matrix>>::read(Vector<Matrix> *data, fstream &fio) {}
// template <>
// void Backup<TestType>::write(const TestType &data, fstream &fio)
// {
//     Backup<Matrix>::write(data.a, fio);
//     Backup<Matrix>::write(data.b, fio);
//     Backup<Matrix>::write(data.c, fio);
// }
// template <>
// void Backup<TestType>::read(TestType &data, fstream &fio)
// {
//     Backup<Matrix>::read(data.a, fio);
//     Backup<Matrix>::read(data.b, fio);
//     Backup<Matrix>::read(data.c, fio);
// }
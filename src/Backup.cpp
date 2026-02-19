#include "Backup.hpp"
#include "Matrix.hpp"

template <>
void Backup<Matrix>::write(const Matrix &data, fstream &fio)
{
    // cout << "?\n";
    if (data.data)
    {
        // cout << data.data[15] << bool(fio) << "\n";
        fio.write(reinterpret_cast<const char *>(&data.n), sizeof(data.n));
        fio.write(reinterpret_cast<const char *>(&data.m), sizeof(data.m));
        // cout << data.n * data.m * sizeof(DataType) << "\n";
        // fio.flush();
        // cout << bool(reinterpret_cast<const char *>(&data.data[0])) << "\n";
        // cout <<
        fio.write(reinterpret_cast<const char *>(&data.data[0]), data.n * data.m * sizeof(DataType));

        // .bad() << "\n";
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
void Backup<Matrix>::read(Matrix &data, fstream &fio)
{
    int n, m;
    fio.read(reinterpret_cast<char *>(&n), sizeof(n));
    fio.read(reinterpret_cast<char *>(&m), sizeof(m));
    Matrix tmp(n, m);
    if (tmp.data)
        fio.read(reinterpret_cast<char *>(tmp.data), n * m * sizeof(DataType));
    data = move(tmp);
}
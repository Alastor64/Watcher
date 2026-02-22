#include "Backup.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Web.hpp"
#include "Data.hpp"
#include "Gradient.hpp"
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
// typedef Inspirer *PInspirer;
template <>
void Backup<Inspirer *>::write(Inspirer *const *data, fstream &fio)
{
    int n;
    if (dynamic_cast<Leaky_ReLu *const>(*data))
    {
        n = int(IDENTITY::Leaky_ReLu);
        fio.write(reinterpret_cast<const char *>(&n), sizeof(n));
        Backup<Leaky_ReLu>::write(dynamic_cast<Leaky_ReLu *const>(*data), fio);
    }
    else if (dynamic_cast<ReLu *const>(*data))
    {
        n = int(IDENTITY::ReLu);
        fio.write(reinterpret_cast<const char *>(&n), sizeof(n));
        Backup<ReLu>::write(dynamic_cast<ReLu *const>(*data), fio);
    }
}
template <>
void Backup<Inspirer *>::read(Inspirer **data, fstream &fio)
{
    int n;
    fio.read(reinterpret_cast<char *>(&n), sizeof(n));
    if (n == int(IDENTITY::Leaky_ReLu))
    {
        *data = new Leaky_ReLu();
        Backup<Leaky_ReLu>::read(dynamic_cast<Leaky_ReLu *>(*data), fio);
    }
    else if (n == int(IDENTITY::ReLu))
    {
        *data = new ReLu();
        Backup<ReLu>::read(dynamic_cast<ReLu *>(*data), fio);
    }
}
template <>
void Backup<Web>::write(const Web *data, fstream &fio)
{
    Backup<Vector<Matrix>>::write(&data->tmps, fio);
    Backup<Vector<Matrix>>::write(&data->cells, fio);
    Backup<Vector<Matrix>>::write(&data->doors, fio);
    Backup<Vector<Matrix>>::write(&data->edges, fio);
    Backup<Inspirer *>::write(&data->inspirer, fio);
}
template <>
void Backup<Web>::read(Web *data, fstream &fio)
{
    Backup<Vector<Matrix>>::read(&data->tmps, fio);
    Backup<Vector<Matrix>>::read(&data->cells, fio);
    Backup<Vector<Matrix>>::read(&data->doors, fio);
    Backup<Vector<Matrix>>::read(&data->edges, fio);
    Backup<Inspirer *>::read(&data->inspirer, fio);
}
template <>
void Backup<Knowledge>::write(const Knowledge *data, fstream &fio)
{
    Backup<Vector<Matrix>>::write(&data->input, fio);
    Backup<Vector<Matrix>>::write(&data->output, fio);
}
template <>
void Backup<Knowledge>::read(Knowledge *data, fstream &fio)
{
    Backup<Vector<Matrix>>::read(&data->input, fio);
    Backup<Vector<Matrix>>::read(&data->output, fio);
}

template <>
void Backup<Gradient>::write(const Gradient *data, fstream &fio)
{
    Backup<Vector<Matrix>>::write(&data->doors, fio);
    Backup<Vector<Matrix>>::write(&data->edges, fio);
}
template <>
void Backup<Gradient>::read(Gradient *data, fstream &fio)
{
    Backup<Vector<Matrix>>::read(&data->doors, fio);
    Backup<Vector<Matrix>>::read(&data->edges, fio);
}
// template <>
// void Backup<>::write(const *data, fstream &fio)
// {
// }
// template <>
// void Backup<>::read(*data, fstream &fio)
// {
// }
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
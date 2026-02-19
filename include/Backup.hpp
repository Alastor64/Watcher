#pragma once
#include "Mytypedef.hpp"
// #include "Matrix.hpp"

// class TestType
// {
// public:
//     Matrix a;
//     template <class... Args>
//     TestType(Args... args) : a(args...) {}
// };

class FileError
{
public:
    const char *what()
    {
        return "Two Backups use the same file!";
    }
};
// template <class T>
// constexpr bool is_specially_stored = std::is_same_v<T, Matrix>;
template <class T>
class Backup
{
    template <class _T>
    friend class Backup;
    static constexpr int VS = std::is_polymorphic_v<T> * sizeof(VPTR);

protected:
    T *data;
    fstream fio;
    void set_FREE()
    {
        fio.seekp(0);
        fio.write(reinterpret_cast<const char *>(&FREE), sizeof(FREE));
        fio.flush();
    }
    void set_USED()
    {
        fio.seekp(0);
        fio.write(reinterpret_cast<const char *>(&USED), sizeof(USED));
        fio.flush();
    }
    int get_state()
    {
        int tmp;
        fio.seekg(0);
        fio.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
        return tmp;
    }

public:
    static void write(const T &data, fstream &fio)
    {
        fio.write(reinterpret_cast<const char *>(&data) + VS, sizeof(T) - VS);
        fio.flush();
    }
    static void read(T &data, fstream &fio)
    {
        fio.read(reinterpret_cast<char *>(&data) + VS, sizeof(T) - VS);
    }

public:
    static constexpr int USED = 1;
    static constexpr int FREE = 0;
    template <typename... Args>
    Backup(const char *fileName, Args &&...args) : data(new T(std::forward<Args>(args)...))
    {
        fio.open(fileName, ios::out | ios::in | ios::binary);
        if (fio)
        {
            if (get_state() != FREE)
                throw FileError();
            fio.close();
        }
        fio.open(fileName, ios::out | ios::trunc | ios::binary);
        set_USED();
        fio.seekp(sizeof(int));
        Backup<T>::write(*data, fio);
        fio.close();
        fio.open(fileName, ios::out | ios::in | ios::binary);
    }
    Backup(const char *fileName) : data(new T())
    {
        // cout << "?\n";
        fio.open(fileName, ios::out | ios::in | ios::binary);
        if (fio)
        {
            if (get_state() != FREE)
                throw FileError();
            fio.seekg(sizeof(int));
            Backup<T>::read(*data, fio);
        }
        else
        {
            fio.open(fileName, ios::out | ios::trunc | ios::binary);
            fio.seekp(sizeof(int));
            Backup<T>::write(*data, fio);
            fio.close();
            fio.open(fileName, ios::out | ios::in | ios::binary);
        }
        set_USED();
    }
    ~Backup()
    {
        set_FREE();
        fio.close();
        delete data;
    }
    Backup(const Backup &) = delete;
    Backup(Backup &&) = delete;
    Backup &operator=(const Backup &) = delete;
    Backup &operator=(Backup &&) = delete;
    T &operator=(const T &tmp)
    {
        return *data = tmp;
    }
    T &operator=(T &&tmp)
    {
        return *data = move(tmp);
    }
    T *operator->()
    {
        return data;
    }
    const T *operator->() const
    {
        return data;
    }
    operator T &()
    {
        return *data;
    }
    template <class Arg>
    auto operator[](Arg index)
    {
        return (*data)[index];
    }
    template <typename... Args>
    auto operator()(Args... args)
    {
        return (*data)(args...);
    }
    void update()
    {
        fio.seekp(sizeof(int));
        write(*data, fio);
    }
};
// template <>
// void Backup<TestType>::write(const TestType &data, fstream &fio)
// {
//     Backup<Matrix>::write(data.a, fio);
// }
// template <>
// void Backup<TestType>::read(TestType &data, fstream &fio)
// {
//     Backup<Matrix>::read(data.a, fio);
// }
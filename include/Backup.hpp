#pragma once
#include "Mytypedef.hpp"
#include <fstream>
class FileError
{
public:
    const char *what()
    {
        return "Two Backups use the same file!";
    }
};
template <class T>
class Backup
{
    typedef std::ios_base ios;
    static constexpr int VS = std::is_polymorphic_v<T> * sizeof(VPTR);

private:
    T data;
    std::fstream fio;
    void write()
    {
        fio.seekp(sizeof(int));
        fio.write(reinterpret_cast<const char *>(&data) + VS, sizeof(T) - VS);
        fio.flush();
    }
    void read()
    {
        fio.seekg(sizeof(int));
        fio.read(reinterpret_cast<char *>(&data) + VS, sizeof(T) - VS);
    }

public:
    static constexpr int USED = 1;
    static constexpr int FREE = 0;
    template <typename... Args>
    Backup(const char *fileName, Args... args) : data(args...)
    {
        fio.open(fileName, ios::out | ios::in | ios::binary);
        if (fio)
        {
            int tmp;
            fio.seekg(0);
            fio.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
            if (tmp != FREE)
                throw FileError();
        }
        fio.close();
        fio.open(fileName, ios::out | ios::trunc | ios::binary);
        fio.seekp(0);
        fio.write(reinterpret_cast<const char *>(&USED), sizeof(USED));
        write();
        fio.close();
        fio.open(fileName, ios::out | ios::in | ios::binary);
    }
    Backup(const char *fileName) : data()
    {
        fio.open(fileName, ios::out | ios::in | ios::binary);
        if (fio)
        {
            int tmp;
            fio.seekg(0);
            fio.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
            if (tmp != FREE)
                throw FileError();
            read();
        }
        else
        {
            fio.close();
            fio.open(fileName, ios::out | ios::trunc | ios::binary);
            write();
            fio.close();
            fio.open(fileName, ios::out | ios::in | ios::binary);
        }
        fio.seekp(0);
        fio.write(reinterpret_cast<const char *>(&USED), sizeof(USED));
        fio.flush();
        // fio.close();
        // fio.open(fileName, ios::out | ios::in | ios::binary);
    }
    ~Backup()
    {
        fio.seekp(0);
        fio.write(reinterpret_cast<const char *>(&FREE), sizeof(FREE));
        fio.close();
    }
    Backup(const Backup &) = delete;
    Backup(Backup &&) = delete;
    Backup &operator=(const Backup &) = delete;
    Backup &operator=(Backup &&) = delete;
    T &operator=(const T &tmp)
    {
        return data = tmp;
    }
    T &operator=(T &&tmp)
    {
        return data = std::move(tmp);
    }
    T *operator->()
    {
        return &data;
    }
    const T *operator->() const
    {
        return &data;
    }
    operator T &()
    {
        return data;
    }
    void update()
    {
        write();
    }
};
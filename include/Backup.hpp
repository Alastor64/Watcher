#pragma once
#include "Mytypedef.hpp"
// #include "Matrix.hpp"

class FileError
{
public:
    const char *what()
    {
        return "Two Backups use the same file!";
    }
};
template <class>
class is_Vector : public std::false_type
{
};
template <class T>
class is_Vector<Vector<T>> : public std::true_type
{
};

template <class T>
class Backup
{
    // template <class _T>
    // friend class Backup;
    // template <class _T *>
    // friend class Backup;

    static constexpr int VS = std::is_polymorphic_v<T> * sizeof(VPTR);

protected:
    static constexpr int USED = 1;
    static constexpr int FREE = 0;
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
    static void write(const T *data, fstream &fio)
    {
        if constexpr (is_Vector<T>::value)
        {
            // cout << "?\n";
            int n = data->data.size();
            fio.write(reinterpret_cast<const char *>(&n), sizeof(n));
            for (int i = 0; i < n; i++)
                Backup<typename decltype(data->data)::value_type>::write(&data->data.at(i), fio);
            fio.flush();
        }
        else
        {
            fio.write(reinterpret_cast<const char *>(data) + VS, sizeof(T) - VS);
            fio.flush();
        }
    }
    static void read(T *data, fstream &fio)
    {
        if constexpr (is_Vector<T>())
        {
            int n;
            typename decltype(data->data)::value_type tmp;
            fio.read(reinterpret_cast<char *>(&n), sizeof(n));
            data->data.clear();
            for (int i = 0; i < n; i++)
            {
                Backup<typename decltype(data->data)::value_type>::read(&tmp, fio);
                data->push(move(tmp));
            }
        }
        else
        {
            fio.read(reinterpret_cast<char *>(data) + VS, sizeof(T) - VS);
        }
    }
    void update()
    {
        fio.seekp(sizeof(int));
        write(data, fio);
    }
    void close()
    {
        set_FREE();
        fio.close();
    }

public:
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
        Backup<T>::write(data, fio);
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
            Backup<T>::read(data, fio);
        }
        else
        {
            fio.open(fileName, ios::out | ios::trunc | ios::binary);
            fio.seekp(sizeof(int));
            Backup<T>::write(data, fio);
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
    template <class Arg>
    decltype(auto) operator-=(Arg &&arg)
    {
        return data->operator-=(std::forward<Arg>(arg));
    }
    // T *&operator=(T *const tmp)
    // {
    //     delete[] data;
    //     data = tmp;
    //     return data;
    // }
    T *operator->()
    {
        return data;
    }
    // const T *operator->() const
    // {
    //     return data;
    // }
    operator T &()
    {
        return *data;
    }
    T &operator*()
    {
        return *data;
    }
    template <class Arg>
    auto operator[](Arg index) -> decltype((*data)[index])
    {
        return (*data)[index];
    }
    template <typename... Args>
    auto operator()(Args... args) -> decltype((*data)(args...))
    {
        return (*data)(args...);
    }
};
template <class T>
class Backup<const T>
{
    static_assert("Backup of const type is meaningless!");
};
// template <class T *>
// class Backup
// {
//     template <class _T>
//     friend class Backup;
//     template <class _T *>
//     friend class Backup;

// protected:
//     void write(const T *data, fstream &fio)
// };

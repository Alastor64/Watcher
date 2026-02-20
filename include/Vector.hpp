#pragma once
#include "Mytypedef.hpp"
#include "Backup.hpp"
template <class T>
class Vector
{
    friend class Backup<Vector<T>>;
    friend class Backup<Vector<T>>;

protected:
    vector<T> data;

public:
    Vector()
    {
        data.clear();
    }
    Vector(const Vector &) = delete;
    Vector(Vector &&) = delete;
    Vector &operator=(const Vector &x)
    {
        if (data.size() != x.data.size())
            throw "unequal size!";
        for (int i = 0; i < data.size(); i++)
            data.at(i) = x.data.at(i);
        return *this;
    }
    Vector &operator=(Vector &&) = delete;
    ~Vector() = default;
    void push(const T &x)
    {
        data.push_back(x);
    }
    void push(T &&x)
    {
        data.push_back(move(x));
    }
    void push(const T &x, int num)
    {
        while (num--)
            data.push_back(x);
    }
    void push(T &&x, int num)
    {
        while (--num)
            data.push_back(x);
        data.push_back(move(x));
    }
    void pop()
    {
        data.pop_back();
    }
    T &operator[](int index)
    {
        return data.at(index);
    }
    friend std::ostream &operator<<(std::ostream &output, const Vector &x)
    {
        for (int i = 0; i < x.data.size(); i++)
            output << x.data.at(i) << "\n";
        return output;
    }
};
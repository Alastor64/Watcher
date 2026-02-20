#include "Matrix.hpp"
#include "Backup.hpp"
#include "Vector.hpp"
#include "Web.hpp"
class pii : public std::pair<int, int>
{
public:
    virtual int abs()
    {
        return std::abs(first) + std::abs(second);
    }
};
DataType r1()
{
    return rand() % 2000 / DataType(1000) - 1;
}
int main()
{
    // Vector<Matrix> tmp;
    // tmp.push(Matrix::identity(2));
    // cin >> tmp[0][0][0];
    // cout << tmp[0][0][0] << "\n";
    using namespace std;
    // cout << sizeof(VPTR);
    try
    {
        Backup<Web> a("webbig", 784, 10, 20, 3, new Leaky_ReLu(0.1), r1); //, 2, 2, 2, 1, new Leaky_ReLu(0.1), r1);
        cout << "doors:\n"
             << a->doors;
        cout << "edges:\n"
             << a->edges;
        a->calculate();
        cout << "cells:\n"
             << a->cells;
        a.update();
    }
    catch (FileError a)
    {
        cout << a.what() << "\n";
    }
    //*/
    return 0;
}
#include "Matrix.hpp"
#include "File.hpp"
#include "FileData.hpp"
#include <array>
// template <typename T>
// void f(T &&x)
// {
//     cout << x << "\n";
// }
// File<Matrix> fin("abab", 0);
// class apo
// {
// public:
//     apo()
//     {
//         cout << "defult\n";
//     }
// };
// class dfo
// {
// public:
//     apo z;
//     dfo()
//     {
//     }
// };
int main()
{
    FileData<std::array<DataType, 3>> a("data", 0);
    std::array<DataType, 3> k;
    for (int i = 7; i < 10; i++)
    {
        k[0] = i * 3;
        k[1] = i * 3 + 1;
        k[2] = i * 3 + 2;
        a.push(k);
    }
    for (int i = 9; i >= 0; i--)
    {
        a.get(k, i);
        std::cout << k[0] << k[1] << k[2] << "\n";
    }
    // dfo a;
    // int a = 954437178;
    // cout << a * 3 + a * 6 << "\n";
    // f(2);
    // int a = 3;
    // f(a);
    // Matrix A(Matrix::scalar(2, 3));
    // Matrix B = -A;
    // Matrix C(2, 2);
    // C = Matrix(A);
    // B = A;
    // B += A;
    // cout << "\n";
    // B += A;
    // cout << B;
    // cout << "\n";
    // B = -A - (A - A - A - (A - A));
    // B = B;
    // B = B + B;
    // B += +-B;
    // cout << "\n";
    // B = B * A;
    // B *= A;
    return 0;
}
#include "Matrix.hpp"
template <typename T>
void f(T &&x)
{
    cout << x << "\n";
}
int main()
{
    // f(2);
    // int a = 3;
    // f(a);
    Matrix A(2, 2);
    Matrix B = -A;
    // B = A;
    // B += A;
    cout << "\n";
    B = B + A + A + A + B - A;
    // B = B;
    // B = B + B;
    // B += +-B;
    // cout << "\n";
    // B = B * A;
    // B *= A;
    return 0;
}
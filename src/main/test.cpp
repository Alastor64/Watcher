#include "Matrix.hpp"
#include <iostream>
#include "Backup.hpp"
class pii : public std::pair<int, int>
{
public:
    virtual int abs()
    {
        return std::abs(first) + std::abs(second);
    }
};
int main()
{

    using namespace std;
    // cout << sizeof(VPTR);
    try
    {
        Backup<pii> a("pii");
        cout << sizeof(fstream) << "\n";
        // a = pair<int, int>(8, 8);
        // a.update();
        // Backup<Matrix> a("data", Matrix::identity(7));
        cout << a->first << " " << a->second << "\n";
        cout << a->abs() << "\n";
        cin >> a->second;
        // Backup<pii> b("pii");
        a.update();
    }
    catch (FileError a)
    {
        cout << a.what() << "\n";
    }
    //*/
    return 0;
}
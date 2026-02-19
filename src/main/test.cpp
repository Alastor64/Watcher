#include "Matrix.hpp"
#include <iostream>
#include "Backup.hpp"
#include <vector>
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
    std::vector<int> vv;
    using namespace std;
    // cout << sizeof(VPTR);
    try
    {
        Backup<Matrix> a("matrix"); //, Matrix::identity(4));
        cout << sizeof(a) << "\n";
        cout << a << "\n";
        // a = pair<int, int>(8, 8);
        // a.update();
        // Backup<Matrix> a("data", Matrix::identity(7));
        // cout << a->first << " " << a->second << "\n";
        // cout << a->abs() << "\n";
        // cin >> a->second;
        // Backup<pii> b("pii");
        cin >> a[0][0];
        a.update();
    }
    catch (FileError a)
    {
        cout << a.what() << "\n";
    }
    //*/
    return 0;
}
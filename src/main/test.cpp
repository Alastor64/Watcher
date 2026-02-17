#include "Matrix.hpp"
#include <iostream>
#include "Backup.hpp"
int main()
{
    using namespace std;
    try
    {
        Backup<pair<int, int>> a("pii");
        // a = pair<int, int>(8, 8);
        // a.update();
        // Backup<Matrix> a("data", Matrix::identity(7));
        cout << a->first << " " << a->second << "\n";
        cin >> a->second;
        Backup<int> b("pii");
        a.update();
    }
    catch (FileError a)
    {
        cout << a.what() << "\n";
    }
    return 0;
}
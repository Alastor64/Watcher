#include "Backup.hpp"
#include <iostream>
#include <fstream>
#include <string>
int main(int argn, const char *args[])
{
    using namespace std;
    // string s;
    // cin >> s;
    fstream f;
    f.open(args[1], ios::out | ios::in | ios::binary);
    if (f)
    {
        int tmp = 0;
        f.seekp(0);
        f.write(reinterpret_cast<const char *>(&tmp), sizeof(tmp));
    }
    else
        cout << "No found\n";
    return 0;
}
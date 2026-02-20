#include "Matrix.hpp"
#include "Backup.hpp"
#include "Vector.hpp"
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
    Vector<Matrix> tmp;
    tmp.push(Matrix::identity(2));
    cin >> tmp[0][0][0];
    cout << tmp[0][0][0] << "\n";
    using namespace std;
    // cout << sizeof(VPTR);
    try
    {
        Backup<Vector<Matrix>> a("matrix"); //, Matrix::identity(4));
        cout << sizeof(a) << "\n";
        // a->push(Matrix::scalar(3, -1));
        // a->push(Matrix::scalar(2, 5));
        cout << a << "\n";
        // a->a = Matrix::identity(2);
        // a->b = Matrix::scalar(2, 3);
        // a->c = Matrix::scalar(3, -1);
        // cout << a->a << a->b << a->c << "\n";
        // a = pair<int, int>(8, 8);
        // a.update();
        // Backup<Matrix> a("data", Matrix::identity(7));
        // cout << a->first << " " << a->second << "\n";
        // cout << a->abs() << "\n";
        // cin >> a->second;
        // Backup<pii> b("pii");
        // cin >> a->a[0][0];
        // decltype(a[0][0][0]) zz;
        cin >> a[0][0][0];
        cout << a[0][0][0] << "\n";
        a.update();
    }
    catch (FileError a)
    {
        cout << a.what() << "\n";
    }
    //*/
    return 0;
}
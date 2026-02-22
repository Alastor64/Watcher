#include "Matrix.hpp"
#include "Backup.hpp"
#include "Vector.hpp"
#include "Web.hpp"
#include "Data.hpp"
#include "Gradient.hpp"
#include <unistd.h>
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
DataType r2()
{
    return r1() * 2;
}
int main()
{
    srand(time(nullptr));
    try
    {
        Backup<Knowledge> testdata("testdata");
        testdata.close();
        // Matrix tmp(2, 1);
        // tmp(0) = 1;
        // tmp(1) = 1;
        // testdata->input.push(tmp);
        // tmp(0) = 1;
        // tmp(1) = 1;
        // testdata->output.push(tmp);
        // testdata.update();
        Backup<Web> web("web"); //, 20, 10, 20, 3, new Leaky_ReLu(0.1), r1);
        // web.close();
        Backup<Web> ans("ans");
        // ans = *web;
        // cout << web->doors << web->edges << web->cells;
        // cout << web->inspirer->df(-1) << "\n";
        DataType min;
        int cnt = 0;
        int st = 100;
        DataType sum = 0;
        const DataType LW = 0.00005;
        const int Lnum = 10000;
        const int N = testdata->input.size();
        for (int i = 0; i < N; i++)
        {
            ans->input() = testdata->input[i];
            ans->calculate();
            sum += DifSqr(ans->output(), testdata->output[i]);
        }
        min = sum;
        cout << min << "\n";
        sleep(1);
        for (int TT = 0; TT < Lnum; TT++)
        {
            sum = 0;
            vector<Gradient> gra;
            gra.clear();
            for (int i = 0; i < N; i++)
            {
                gra.push_back(*web);

                web->input() = testdata->input[i];
                web->calculate();
                sum += DifSqr(web->output(), testdata->output[i]);
                gra.back().calculate(web, testdata->output[i], dDifSqr);
                // cout << web->output() << "\n"
                //      << testdata->output[0] << "\n"
                //      << dDifSqr(web->output(), testdata->output[0]) << "\n"
                //      << gra.doors << gra.edges;
                gra.back() *= LW;
            }
            cout << sum << "\n";
            if (sum < 0 || (sum > 1000 * N && TT))
                break;
            if (sum < min)
            {
                min = sum;
                ans = *web;
                cnt++;
                if (cnt >= st)
                {
                    cnt = 0;
                    ans.update();
                    cout << "saved\n";
                    // sleep(1);
                }
            }
            for (int i = 0; i < N; i++)
            {
                web -= gra.at(i);
            }
        }
        ans.update();
        web.update();
    }
    catch (FileError a)
    {
        cout << a.what() << "\n";
    }
    //*/
    return 0;
}
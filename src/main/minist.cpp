#include "Matrix.hpp"
#include "Backup.hpp"
#include "Vector.hpp"
#include "Web.hpp"
#include "Data.hpp"
#include "Gradient.hpp"
#include <unistd.h>
constexpr DataType LW = 0.0000001;
constexpr int Lnum = 10000;
constexpr DataType EP = 20;
int needcnt;
DataType r1()
{
    return rand() % 2000 / DataType(1000) - 1;
}
DataType r2()
{
    return r1() * 2;
}
bool need(const Matrix &reslut, const Matrix &answer)
{
    int mxr = 0, mxa = 0;
    for (int i = 1; i < reslut.height(); i++)
        if (reslut(mxr) < reslut(i))
            mxr = i;
    for (int i = 1; i < answer.height(); i++)
        if (answer(mxa) < answer(i))
            mxa = i;
    return mxr != mxa;
}
void down(Backup<Web> &web, const Knowledge &data, const int &N)
{
    Gradient sum(web), tmp(web);
    for (int i = 0; i < N; i++)
    {
        web->input() = data.input[i];
        web->calculate();
        if (DifSqr(web->output(), data.output[i]) > EP * EP / 4)
        // if (need(web->output(), data.output[i]))
        {
            needcnt++;
            tmp.calculate(web, data.output[i], dDifSqr);
            sum += tmp;
        }
    }
    if (!needcnt)
        return;
    sum *= LW;
    sum *= 1 / DataType(needcnt);
    web -= sum;
}
void learn(Backup<Web> &web, const Knowledge &data, const int &N)
{
    Gradient tmp(web);
    for (int i = 0; i < N; i++)
    {
        web->input() = data.input[i];
        web->calculate();
        if (DifSqr(web->output(), data.output[i]) > EP * EP / 4)
        // if (need(web->output(), data.output[i]))
        {
            needcnt++;
            tmp.calculate(web, data.output[i], dDifSqr);
            tmp *= LW;
            web -= tmp;
        }
    }
}
void recite(Backup<Web> &web, const Knowledge &data, const int &N)
{
    Gradient tmp(web);
    for (int i = 0; i < N; i++)
    {
        bool fg = 0;
        web->input() = data.input[i];
        web->calculate();
        DataType DS;
        while ((DS = DifSqr(web->output(), data.output[i])) > EP * EP)
        {
            // cout << DS << "\n";
            fg = 1;
            tmp.calculate(web, data.output[i], dDifSqr);
            tmp *= LW;
            web -= tmp;
            web->input() = data.input[i];
            web->calculate();
        }
        needcnt += fg;
        if (fg)
            cout << needcnt << ":" << i << " ";
    }
    cout << "\n";
}
DataType sd(Backup<Web> &web, const Knowledge &data)
{
    DataType sum = 0;
    for (int i = 0; i < data.input.size(); i++)
    {
        web->input() = data.input[i];
        web->calculate();
        sum += DifSqr(web->output(), data.output[i]);
    }
    return sum;
}
void train()
{
    srand(time(nullptr));
    try
    {
        Knowledge testdata;
        testdata.load_idxX_ubyte(0, 30000);
        for (int i = 0; i < testdata.output.size(); i++)
        {
            testdata.output[i] *= EP;
        }
        Backup<Web> web("web"); //, 784, 10, 20, 4, new Leaky_ReLu(0.1), r1);
        Backup<Web> ans("ans");
        // ans = *web;
        DataType min = sd(ans, testdata);
        cout << min << "\n";
        sleep(1);

        int cnt = 0;
        int st = 1;
        const int N = testdata.input.size();
        for (int TT = 0; TT < Lnum; TT++)
        {
            needcnt = 0;
            // down(web, testdata, N);
            learn(web, testdata, N);
            // recite(web, testdata, N);
            DataType sum = sd(web, testdata);
            cout << TT << ":" << sum << " " << needcnt << "\n";
            if (sum < 0 || (sum > 1000 * EP * EP * N && TT))
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
            if (TT % 100 == 0)
            {
                web.update();
                cout << "web saved\n";
            }
            if (!needcnt)
                break;
        }
        ans.update();
        web.update();
    }
    catch (FileError a)
    {
        cout << a.what() << "\n";
    }
}
void test()
{
    Knowledge data;
    data.load_idxX_ubyte(0, 30000);
    Backup<Web> web("ans");
    web.close();
    needcnt = 0;
    for (int i = 0; i < data.input.size(); i++)
    {
        web->input() = data.input[i];
        web->calculate();
        if (need(web->output(), data.output[i]))
            needcnt++;
    }
    cout << needcnt << "\n";
}
int main()
{
    train();
    // test();
    return 0;
}
#include "Backup.hpp"
#include "Web.hpp"
#include "Data.hpp"
#include "Gradient.hpp"
#include <unistd.h>
constexpr DataType LW = 0.0001;
constexpr int LN = 10000;
DataType r1()
{
    return rand() % 2000 / DataType(1000) - 1;
}
void learn(Backup<Web> &web, Backup<Knowledge> &data)
{
    for (int i = 0; i < data->input.size(); i++)
    {
        web->input() = data->input[i];
        web->calculate();
        Gradient gra(web);
        gra.calculate(web, data->output[i], dDifSqr);
        gra *= LW;
        web -= gra;
    }
}
DataType sd(Backup<Web> &web, Backup<Knowledge> &data)
{
    DataType sum = 0;
    for (int i = 0; i < data->input.size(); i++)
    {
        web->input() = data->input[i];
        web->calculate();
        sum += DifSqr(web->output(), data->output[i]);
    }
    return sum;
}
int main()
{
    Backup<Knowledge> data("testdata");
    data.close();
    Backup<Web> web("Lweb"); //, 20, 10, 20, 3, new Leaky_ReLu(0.1), r1);
    Backup<Web> ans("Lans");
    // ans = *web;
    // ans.update();
    DataType min = sd(ans, data);
    cout << min << "\n";
    sleep(1);
    for (int T = 0; T < LN; T++)
    {
        learn(web, data);
        DataType su;
        cout << (su = sd(web, data)) << "\n";
        if (su < 0)
        {
            cout << web->doors << web->edges;
            return 0;
        }
        if (su < min)
        {
            min = su;
            ans = *web;
            ans.update();
        }
    }
    web.update();
    return 0;
}
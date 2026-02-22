#include "Backup.hpp"
#include "Data.hpp"
void XOR()
{
    Backup<Knowledge> data("testdata");
    data->clear();
    Matrix tmp(2, 1);
    tmp(0) = 0;
    tmp(1) = 0;
    data->input.push(tmp);
    tmp(0) = 1;
    data->input.push(tmp);
    tmp(1) = 1;
    data->input.push(tmp);
    tmp(0) = 0;
    data->input.push(tmp);
    Matrix tmp2(2, 1);
    tmp2(0) = 1;
    tmp2(1) = 0;
    data->output.push(tmp2);
    data->output.push(tmp);
    data->output.push(tmp2);
    data->output.push(tmp);
    cout << data->input << data->output;
    data.update();
}
void addition()
{
    Backup<Knowledge> data("testdata");
    data->clear();
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Matrix tmp(20, 1);
            tmp(i) = 1;
            tmp(j + 10) = 1;
            data->input.push(tmp);
            Matrix tmp2(10, 1);
            tmp2((i + j) % 10) = 1;
            data->output.push(tmp2);
        }
    }
    data.update();
}
int main()
{
    addition();
    return 0;
}
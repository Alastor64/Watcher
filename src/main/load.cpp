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
void MNIST()
{
    Backup<Knowledge> data("minist-train");
    data->load_idxX_ubyte(0, 60000);
    data.update();
}
int main()
{
    // MNIST();
    Backup<Knowledge> data("minist-train");
    data.close();
    Backup<Knowledge> sm("minist-train-half1");
    for (int i = 0; i < 30000; i++)
    {
        sm->input.push(data->input[i]);
        sm->output.push(data->output[i]);
    }
    sm.update();
    Backup<Knowledge> sm2("minist-train-half2");
    for (int i = 30000; i < 60000; i++)
    {
        sm2->input.push(data->input[i]);
        sm2->output.push(data->output[i]);
    }
    sm2.update();
    // for (int t = 0; t < 10; t++)
    //     for (int i = 0; i < 28; i++)
    //     {
    //         for (int j = 0; j < 28; j++)
    //         {
    //             DataType tmp = sm->input[t](i * 28 + j);
    //             if (tmp < 0.25)
    //                 cout << " ";
    //             else if (tmp < 0.5)
    //                 cout << ".";
    //             else if (tmp < 0.75)
    //                 cout << "%";
    //             else if (tmp <= 1)
    //                 cout << "#";
    //             else
    //                 throw;
    //         }
    //         cout << "\n";
    //     }
    return 0;
}
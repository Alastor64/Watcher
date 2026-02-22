#include "Data.hpp"

void Knowledge::load_idxX_ubyte()
{
    fstream fi("train-images.idx3-ubyte", ios::in | ios::binary);
    int tmp, n;
    Backup<int>::read(&tmp, fi);
    if (tmp != 2051)
        throw "wrong file!";
    Backup<int>::read(&n, fi);
    int h, w;
    Backup<int>::read(&h, fi);
    Backup<int>::read(&w, fi);
    unsigned char bit;
    Matrix pic(h * w, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < h * w; j++)
        {
            Backup<unsigned char>::read(&bit, fi);
            pic(j) = bit / DataType(255);
        }
        input.push(pic);
    }
    fi.close();
    fi.open("train-labels.idx1-ubyte", ios::in | ios::binary);
    Backup<int>::read(&tmp, fi);
    if (tmp != 2049)
        throw "wrong file!";
    Backup<int>::read(&tmp, fi);
    if (tmp != n)
        throw "mismatching";
    for (int i = 0; i < n; i++)
    {
        Backup<unsigned char>::read(&bit, fi);
        if (bit > 9)
            throw "invalid data!";
        pic = Matrix(10, 1);
        pic(bit) = 1;
        output.push(pic);
    }
}
void Knowledge::clear()
{
    input.clear();
    output.clear();
}
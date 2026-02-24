#include "Data.hpp"

void Knowledge::load_idxX_ubyte(int L, int R)
{
    fstream fi("train-images.idx3-ubyte", ios::in | ios::binary);
    int tmp, n;
    Backup<int>::read(&tmp, fi);
    if (tmp != 2051)
        throw "wrong file!";
    Backup<int>::read(&n, fi);
    if (n < R)
        throw "file too small!";
    int h, w;
    Backup<int>::read(&h, fi);
    Backup<int>::read(&w, fi);
    unsigned char bit;
    Matrix pic(h * w, 1);
    fi.seekg(4 * sizeof(int) + L * sizeof(unsigned char) * h * w);
    for (int i = L; i < R; i++)
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
    fi.seekg(2 * sizeof(int) + L * sizeof(unsigned char));
    for (int i = L; i < R; i++)
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
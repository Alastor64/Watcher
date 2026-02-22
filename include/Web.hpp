#pragma once
#include "Mytypedef.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Inspirer.hpp"
class Web
{
    friend class Backup<Web>;

public:
    Vector<Matrix> cells;
    Vector<Matrix> tmps;
    Vector<Matrix> doors;
    Vector<Matrix> edges;
    Inspirer *inspirer;
    Web();
    Web(int Inum, int Onum, int Mnum, int Mwidth, Inspirer *_inspirer, DataType (*Rand)());
    ~Web();
    void calculate();
    Matrix &output();
    Matrix &input();
    Web &operator-=(const Gradient &x);
    Web &operator=(const Web &x);
};
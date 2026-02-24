#pragma once
#include "Vector.hpp"
#include "Matrix.hpp"
class Knowledge
{
public:
    void load_idxX_ubyte(int, int);
    void clear();
    Vector<Matrix> input;
    Vector<Matrix> output;
};
#pragma once
#include "Vector.hpp"
#include "Matrix.hpp"
class Knowledge
{
public:
    void load_idxX_ubyte();
    void clear();
    Vector<Matrix> input;
    Vector<Matrix> output;
};
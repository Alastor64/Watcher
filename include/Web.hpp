#pragma once
#include "Mytypedef.hpp"
#include "Matrix.hpp"
class Web
{
    friend class Backup<Web>;

public:
    Matrix input;
    Matrix middle;
    Matrix output;
};
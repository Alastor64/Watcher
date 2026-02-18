#pragma once
#include <iostream>
#include <fstream>
typedef double DataType;
using std::cin;
using std::cout;
using std::move;
typedef std::ios_base ios;
typedef std::fstream fstream;
class VPTR
{
    virtual ~VPTR() {}
};
class Matrix;
template <class T>
class Backup;
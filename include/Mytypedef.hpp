#pragma once
#include <iostream>
#include <fstream>
#include <vector>
typedef double DataType;
using std::cin;
using std::cout;
using std::move;
using std::vector;
typedef std::ios_base ios;
typedef std::fstream fstream;
class VPTR
{
    virtual ~VPTR() {}
};
class Matrix;
class Web;
template <class T>
class Backup;
template <class T>
class Vector;
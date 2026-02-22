#pragma once
#include "Vector.hpp"
#include "Web.hpp"
#include "Data.hpp"
DataType DifSqr(const Matrix &result, const Matrix &answer);
Matrix dDifSqr(const Matrix &result, const Matrix &answer);
class Gradient
{
public:
    Gradient();
    Gradient(const Web &web);
    void calculate(Web &web, const Matrix &output, Matrix (*dLossFunc)(Matrix const &result, Matrix const &answer));
    Vector<Matrix> doors;
    Vector<Matrix> edges;
    Gradient &operator*=(const DataType &x) &;
};
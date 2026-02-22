#include "Gradient.hpp"
DataType DifSqr(const Matrix &result, const Matrix &answer)
{
    DataType sum = 0;
    if (result.height() != answer.height() || result.width() != answer.width())
        throw "invalid args!";
    for (int i = 0; i < result.height(); i++)
        for (int j = 0; j < result.width(); j++)
            sum += (result[i][j] - answer[i][j]) * (result[i][j] - answer[i][j]);
    return sum;
}
Matrix dDifSqr(const Matrix &result, const Matrix &answer)
{
    return (result - answer) * 2;
}

Gradient::Gradient() = default;
Gradient::Gradient(const Web &web) : doors(web.doors), edges(web.edges) {}
void Gradient::calculate(Web &web, const Matrix &output, Matrix (*dLossFunc)(Matrix const &result, Matrix const &answer))
{
    // web.input() = input;
    // web.calculate();
    doors.back() = dLossFunc(web.output(), output);
    for (int i = 0; i < doors.back().height(); i++)
        doors.back()(i) *= web.inspirer->df(web.tmps.back()(i));
    for (int i = doors.size() - 2; i >= 0; i--)
    {
        edges[i] = doors[i + 1] * web.cells[i].T();
        doors[i] = web.edges[i].T() * doors[i + 1];
        for (int j = 0; j < doors[i].height(); j++)
            doors[i](j) *= web.inspirer->df(web.tmps[i](j));
    }
}
Gradient &Gradient::operator*=(const DataType &x) &
{
    for (int i = 0; i < doors.size(); i++)
        doors[i] *= x;
    for (int i = 0; i < edges.size(); i++)
        edges[i] *= x;
    return *this;
}
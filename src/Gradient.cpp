#include "Gradient.hpp"
#include "Vector.hpp"
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
constexpr DataType sqr(const DataType &x)
{
    return x * x;
}
// DataType Dif01(const Matrix &result, const Matrix &answer)
// {
//     DataType sum = 0;
//     if (result.height() != answer.height() || result.width() != answer.width())
//         throw "invalid args!";
//     for (int i = 0; i < result.height(); i++)
//         for (int j = 0; j < result.width(); j++)
//         {
//             if (answer[i][j] > 0.5)
//             {
//                 if (result[i][j] > 1)
//                     sum += sqr(result[i][j] - 1);
//                 else if (result[i][j] > 0.5)
//                     sum += 0.1 * (1 - result[i][j]);
//                 else
//                     sum += sqr(result[i][j] - 0.55) - sqr(0.05) + 0.05;
//             }
//         }
//     return sum;
// }

Gradient::Gradient() = default;
Gradient::Gradient(const Web &web)
{
    for (int i = 0; i < web.doors.size(); i++)
        doors.push(Matrix(web.doors[i].height(), web.doors[i].width()));
    for (int i = 0; i < web.edges.size(); i++)
        edges.push(Matrix(web.edges[i].height(), web.edges[i].width()));
}
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
Gradient &Gradient::operator+=(const Gradient &x) &
{
    doors += x.doors;
    edges += x.edges;
    return *this;
}
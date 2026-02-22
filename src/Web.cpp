#include "Web.hpp"
#include "Gradient.hpp"
Web::Web()
{
    inspirer = nullptr;
}
Web::Web(int Inum, int Onum, int Mnum, int Mwidth, Inspirer *_inspirer, DataType (*Rand)())
{
    inspirer = _inspirer;
    cells.push(Matrix(Inum, 1));
    for (int i = 0; i < Mwidth; i++)
    {
        cells.push(Matrix(Mnum, 1));
    }
    cells.push(Matrix(Onum, 1));
    tmps = cells;
    for (int i = 0; i < cells.size(); i++)
        doors.push(Matrix(cells[i].height(), cells[i].width(), Rand));
    for (int i = 1; i < cells.size(); i++)
        edges.push(Matrix(cells[i].height(), cells[i - 1].height(), Rand));
}
Web::~Web()
{
    delete[] inspirer;
}
void Web::calculate()
{
    for (int i = 0; i < cells.size() - 1; i++)
    {
        cells[i] = tmps[i] + doors[i];
        cells[i].inspire(inspirer);
        tmps[i + 1] = edges[i] * cells[i];
    }
    cells.back() = tmps.back() + doors.back();
    cells.back().inspire(inspirer);
}
Matrix &Web::output()
{
    return cells.back();
}
Matrix &Web::input()
{
    return tmps.front();
}
Web &Web::operator-=(const Gradient &x)
{
    doors -= x.doors;
    edges -= x.edges;
    return *this;
}
Web &Web::operator=(const Web &x)
{
    cells = x.cells;
    doors = x.doors;
    edges = x.edges;
    tmps = x.tmps;
    delete inspirer;
    inspirer = x.inspirer->clone();
    return *this;
}
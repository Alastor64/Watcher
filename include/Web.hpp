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
    Vector<Matrix> doors;
    Vector<Matrix> edges;
    Inspirer *inspirer;
    Web()
    {
        inspirer = nullptr;
    }
    Web(int Inum, int Onum, int Mnum, int Mwidth, Inspirer *_inspirer, DataType (*Rand)())
    {
        inspirer = _inspirer;
        cells.push(Matrix(Inum, 1));
        for (int i = 0; i < Mwidth; i++)
            cells.push(Matrix(Mnum, 1));
        cells.push(Matrix(Onum, 1));
        for (int i = 0; i < cells.size(); i++)
            doors.push(Matrix(cells[i].height(), cells[i].width(), Rand));
        for (int i = 1; i < cells.size(); i++)
            edges.push(Matrix(cells[i].height(), cells[i - 1].height(), Rand));
    }
    ~Web()
    {
        delete[] inspirer;
    }
    void calculate()
    {
        for (int i = 0; i < cells.size() - 1; i++)
        {
            cells[i] += doors[i];
            cells[i].inspire(inspirer);
            cells[i + 1] = edges[i] * cells[i];
        }
        cells.back() += doors.back();
        cells.back().inspire(inspirer);
    }
    Matrix &output()
    {
        return cells.back();
    }
    Matrix &input()
    {
        return cells.front();
    }
};
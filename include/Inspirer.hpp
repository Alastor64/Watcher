#pragma once
#include "Mydef.hpp"
class Inspirer
{
public:
    virtual DataType f(const DataType &) const = 0;
    virtual DataType df(const DataType &) const = 0;
};
class ReLu : public Inspirer
{
public:
    DataType f(const DataType &) const override;
    DataType df(const DataType &) const override;
};
class Leaky_ReLu : public ReLu
{
protected:
    const DataType k;

public:
    Leaky_ReLu(const DataType &);
    DataType f(const DataType &) const override;
    DataType df(const DataType &) const override;
};
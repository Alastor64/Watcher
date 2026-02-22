#pragma once
#include "Mytypedef.hpp"
enum class IDENTITY
{
    ReLu,
    Leaky_ReLu,
};
class Inspirer
{
public:
    Inspirer();
    virtual DataType f(const DataType &) const = 0;
    virtual DataType df(const DataType &) const = 0;
    virtual Inspirer *clone() const = 0;
};
class ReLu : public Inspirer
{
public:
    ReLu();
    DataType f(const DataType &) const override;
    DataType df(const DataType &) const override;
    Inspirer *clone() const override;
};
class Leaky_ReLu : public ReLu
{
protected:
    DataType k;

public:
    Leaky_ReLu();
    Leaky_ReLu(const DataType &);
    DataType f(const DataType &) const override;
    DataType df(const DataType &) const override;
    Inspirer *clone() const override;
};
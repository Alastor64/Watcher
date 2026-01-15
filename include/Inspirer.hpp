#pragma once
#include "Mytypedef.hpp"
class Inspirer
{
public:
    virtual DT f(const DT &) = 0;
    virtual DT df(const DT &) = 0;
};
class ReLu : public Inspirer
{
public:
    DT f(const DT &) override;
    DT df(const DT &) override;
};
class Leaky_ReLu : public ReLu
{
protected:
    const DT k;

public:
    Leaky_ReLu(const DT &);
    DT f(const DT &) override;
    DT df(const DT &) override;
};
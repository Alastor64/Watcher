#include "Inspirer.hpp"
DT ReLu::f(const DT &x)
{
    if (x > 0)
        return x;
    return 0;
}
DT ReLu::df(const DT &x)
{
    if (x > 0)
        return 1;
    return 0;
}
DT Leaky_ReLu::f(const DT &x)
{
    if (x > 0)
        return x;
    return x * k;
}
DT Leaky_ReLu::df(const DT &x)
{
    if (x > 0)
        return 1;
    return k;
}
Leaky_ReLu::Leaky_ReLu(const DT &_k) : k(_k)
{
}
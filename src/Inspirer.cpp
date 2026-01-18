#include "Inspirer.hpp"
DataType ReLu::f(const DataType &x) const
{
    if (x > 0)
        return x;
    return 0;
}
DataType ReLu::df(const DataType &x) const
{
    if (x > 0)
        return 1;
    return 0;
}
DataType Leaky_ReLu::f(const DataType &x) const
{
    if (x > 0)
        return x;
    return x * k;
}
DataType Leaky_ReLu::df(const DataType &x) const
{
    if (x > 0)
        return 1;
    return k;
}
Leaky_ReLu::Leaky_ReLu(const DataType &_k) : k(_k)
{
}
#include "test.h"

test::test()
{
    //ctor
}

test::~test()
{
    //dtor
}

test::test(const test& other)
{
    //copy ctor
}

test& test::operator=(const test& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

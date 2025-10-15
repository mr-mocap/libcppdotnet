#include <libcppdotnet/System/PreProcessor/Contracts.hpp>

import <cstdlib>;
import <cassert>;

import System.ValueTuple;

namespace TestValueTuple
{

void DefaultConstructed()
{
    {
        System::ValueTuple<> t;

        UNUSED(t);
    }
    {
        System::ValueTuple<int> t;

        assert( t.Item<0>() == 0 );
    }
    {
        System::ValueTuple<int, int> t;

        assert( t.Item<0>() == 0 );
        assert( t.Item<1>() == 0 );
    }
}

void Run()
{
    DefaultConstructed();
}

}

int main(void)
{
    TestValueTuple::Run();
    return EXIT_SUCCESS;
}

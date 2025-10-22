module;

#include <libcppdotnet/System/PreProcessor/Contracts.hpp>

module System.Diagnostics.Debugger;

import <string_view>;

namespace System::Diagnostics
{

void Debugger::Log(int level, std::string_view category, std::string_view message)
{
    // assert(category.size() <= 256);

    UNUSED(level);
    UNUSED(category);
    UNUSED(message);

    // TODO: FIXME (in C++23?)
}

}

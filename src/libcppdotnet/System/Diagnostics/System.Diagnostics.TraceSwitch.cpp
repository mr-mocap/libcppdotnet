module System.Diagnostics.TraceSwitch;

import <string_view>;

import System.Diagnostics.TraceLevel;

namespace System::Diagnostics
{

TraceSwitch::TraceSwitch(std::string_view display_name, std::string_view description)
    :
    Switch( display_name, description )
{
}

TraceSwitch::TraceSwitch(std::string_view display_name, std::string_view description, std::string_view default_switch_value)
    :
    Switch( display_name, description, default_switch_value )
{
}

TraceLevel TraceSwitch::Level() const
{
    return _trace_level;
}

void TraceSwitch::Level(TraceLevel new_level)
{
    _trace_level = new_level;
}

bool TraceSwitch::TraceError()   const
{
    return _trace_level >= TraceLevel::Error;
}

bool TraceSwitch::TraceWarning() const
{
    return _trace_level >= TraceLevel::Warning;
}

bool TraceSwitch::TraceInfo()    const
{
    return _trace_level >= TraceLevel::Info;
}

bool TraceSwitch::TraceVerbose() const
{
    return _trace_level >= TraceLevel::Verbose;
}

}

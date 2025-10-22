module;

#include <libcppdotnet/System/PreProcessor/Contracts.hpp>

module System.Diagnostics.SourceSwitch;

import <string_view>;

import System.Exception;
import System.Convert;
import System.Diagnostics.SourceLevels;

namespace System::Diagnostics
{

SourceSwitch::SourceSwitch(std::string_view display_name, std::string_view default_switch_value)
    :
    Switch( display_name, {}, default_switch_value )
{
}

SourceSwitch::SourceSwitch(std::string_view display_name)
    :
    Switch( display_name, {} )
{
}

SourceSwitch SourceSwitch::Make(std::string_view display_name, std::string_view default_switch_value)
{
    Diagnostics::SourceLevels converted{ Convert::ToType(default_switch_value, Diagnostics::SourceLevels::Off) };

    UNUSED(converted);

    return SourceSwitch( display_name, default_switch_value );
}

SourceLevels SourceSwitch::Level()
{
    return static_cast<SourceLevels>( SwitchSetting() );
}

void SourceSwitch::OnValueChanged()
{
    Diagnostics::SourceLevels converted = Convert::ToType(_value, Diagnostics::SourceLevels::Off);

    SwitchSetting( static_cast<int>(converted) );
}

}

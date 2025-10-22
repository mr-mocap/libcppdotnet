module System.Diagnostics.ActivityTraceId;

import <string_view>;

import System.ReadOnlySpan;
import System.Guid;

namespace System::Diagnostics
{

ActivityTraceId ActivityTraceId::CreateRandom()
{
    return ActivityTraceId( Guid::NewGuid() );
}

ActivityTraceId ActivityTraceId::CreateFromString(ReadOnlySpan<char> input)
{
    // We expect the "N" format for the string
    if ( input.Length() != 32 )
        ThrowWithTarget( ArgumentOutOfRangeException( "input", "Does not have exactly 32 Hex characters" ) );

    // Now let the Guid::Parse() handle any other checking...
    std::string_view input_as_string_view( input.begin(), input.end() );

    return ActivityTraceId( Guid::Parse( input_as_string_view ) );
}

ActivityTraceId ActivityTraceId::CreateFromBytes(ReadOnlySpan<std::byte> id_data)
{
    return ActivityTraceId( Guid( id_data ) );
}

}

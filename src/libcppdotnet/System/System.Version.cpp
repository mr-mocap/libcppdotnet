module System.Version;

import <vector>;
import <cstring>;
import <cstdlib>;
import <format>;

import System.Convert;

namespace
{

std::vector<int> Append(std::vector<int> &&input, const std::vector<int> &other)
{
    for (int i : other)
        input.push_back( i );
    return std::move(input);
}

std::vector<int> ToInts(std::string_view input, const char separator = '.')
{
    auto pos = input.find_first_of( separator );

    if ( pos == std::string_view::npos )
    {
        std::string s{ input };
        int converted_value = std::atoi( s.c_str() );

        return { converted_value };
    }

    std::string s{ input.substr( 0, pos ) };
    int converted_value = std::atoi( s.c_str() );

    input.remove_prefix( pos + 1 );
    if ( input.empty() )
        return std::vector<int>(1, converted_value);

    return Append( std::vector<int>(1, converted_value), ToInts(input) );
}

}

namespace System
{

Version::Version(std::string_view input)
{
    Version result{ Parse( input ) };

    *this = result;
}

Version Version::Parse(std::string_view input)
{
    std::vector<int> values{ ::ToInts(input) };

    if ( values.size() > 3)
        return Version( values[0], values[1], values[2], values[3] );
    if ( values.size() > 2)
        return Version( values[0], values[1], values[2] );
    if ( values.size() > 1)
        return Version( values[0], values[1] );
    
    Version result;

    result._major = values[0];
    return result;
}

std::string Version::ToString() const
{
    std::string result = std::format("{}.{}", Major(), Minor() );

    if ( Build() != -1 )
        result.append( std::format(".{}", Build()) );
    
    if ( Revision() != -1 )
        result.append( std::format(".{}", Revision()) );
    
    return result;
}

std::string Version::ToString(int field_count) const
{
    if ( (field_count < 0) || (field_count > 4) )
        ThrowWithTarget( ArgumentOutOfRangeException{ "field_count" } );
    
    if ( field_count == 0 )
        return {};

    if ( field_count == 1 )
        return std::format("{}", Major());

    if ( field_count == 2 )
        return std::format("{}.{}", Major(), Minor() );

    if ( field_count == 3 )
    {
        if ( Build() == -1 )
            ThrowWithTarget( ArgumentOutOfRangeException{ "field_count", "Build() is not set" } );

        return std::format("{}.{}.{}", Major(), Minor(), Build() );
    }

    if ( field_count == 4 )
    {
        if ( Revision() == -1 )
            ThrowWithTarget( ArgumentOutOfRangeException{ "field_count", "Revision() is not set" } );

        return std::format("{}.{}.{}.{}", Major(), Minor(), Build(), Revision());
    }

    return {};
}

}

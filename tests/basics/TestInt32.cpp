#include <libcppdotnet/System/PreProcessor/Contracts.hpp>

import <cstdlib>;
import <cassert>;

import System.Int32;

namespace TestInt32
{

using namespace System;

static std::int32_t FunctionTakingStdInt32(const std::int32_t converted)
{
    return converted;
}

void DefaultConstructsToZero()
{
    Int32 a;

    assert( a == 0 );
}

void ConstructingFromAConstantInteger()
{
    Int32 a(32);
    Int32 b{66};

    assert( a == 32 );
    assert( b == 66 );
}

void AutomaticConversionToStdInt32WhenCallingFunction()
{
    Int32 a(17);

    assert( FunctionTakingStdInt32( a ) == 17 );
}

void GetTypeCode()
{
    Int32 a(17);

    assert( a.GetTypeCode() == TypeCode::Int32 );
}

void ToBoolean()
{
    {
        Int32 a(17);

        assert( a.ToBoolean() == true );
    }
    {
        Int32 a(0);

        assert( a.ToBoolean() == false );
    }
}

void ToByte()
{
    assert( Int32{64}.ToByte() == std::byte{64} );
}

void ToChar()
{
    assert( Int32{22}.ToChar() == char{22} );
}

void ToInt16()
{
    assert( Int32{22}.ToInt16() == std::int16_t{22} );
    assert( Int32{32767}.ToInt16() == std::int16_t{32767} ); // Highest Value
    assert( Int32{0}.ToInt16() == std::int16_t{0} );
    assert( Int32{-1}.ToInt16() == std::int16_t{-1} );
    assert( Int32{-32768}.ToInt16() == std::int16_t{-32768} ); // Lowest Value (negative)
}

void ToInt32()
{
    assert( Int32{22}.ToInt32() == std::int32_t{22} );
    assert( Int32{2147483647}.ToInt32() == std::int32_t{2147483647} ); // Highest Value
    assert( Int32{0}.ToInt32() == std::int32_t{0} );
    assert( Int32{-1}.ToInt32() == std::int32_t{-1} );
    assert( Int32{-2147483648}.ToInt32() == std::int32_t{-2147483648} ); // Lowest Value (negative)
}

void ToSingle()
{
    assert( Int32{22}.ToSingle() == 22.0f );
    assert( Int32{0}.ToInt32() == 0.0f );
    assert( Int32{-1}.ToInt32() == -1.0f );
}

void ToDouble()
{
    assert( Int32{22}.ToSingle() == 22.0 );
    assert( Int32{0}.ToInt32() == 0.0 );
    assert( Int32{-1}.ToInt32() == -1.0 );
}

void ToString()
{
    assert( Int32{22}.ToString() == "22" );
    assert( Int32{0}.ToString() == "0" );
    assert( Int32{-1}.ToString() == "-1" );
}

void Equality()
{
    Int32 number{65536};

    assert( number == 65536 );
    assert( 65536 == number );

    // With std::int16_t
    {
        std::int16_t int16 = 32767;

        assert( number != int16 );
        assert( int16 != number );
        assert( number != 32767 );
        assert( 32767 != number );
    }

    // With std::int8_t
    {
        std::int8_t int8 = 127;

        assert( number != int8 );
        assert( int8 != number );
        assert( number != 127 );
        assert( 127 != number );
    }
}

void TestINumberBase()
{
    assert( Int32::Zero() == 0 );
    assert( Int32::One() == 1 );

    assert( Int32::Abs(0) == 0 );
    assert( Int32::Abs(27) == 27 );
    assert( Int32::Abs(-1) == 1 );
    assert( Int32::Abs(-27) == 27 );

    assert(  Int32::IsEvenInteger(0) );
    assert( !Int32::IsEvenInteger(1) );
    assert(  Int32::IsEvenInteger(2) );
    assert( !Int32::IsEvenInteger(3) );
    assert(  Int32::IsEvenInteger(1000000) );
    assert( !Int32::IsEvenInteger(-1) );
    assert(  Int32::IsEvenInteger(-2) );

    assert(  Int32::IsNegative(-1) );
    assert( !Int32::IsNegative(0) );
    assert( !Int32::IsNegative(1) );

    assert( !Int32::IsOddInteger(0) );
    assert(  Int32::IsOddInteger(1) );
    assert( !Int32::IsOddInteger(2) );
    assert(  Int32::IsOddInteger(3) );
    assert(  Int32::IsOddInteger(-1) );
    assert( !Int32::IsOddInteger(-2) );

    assert( !Int32::IsPositive(0) );
    assert(  Int32::IsPositive(1) );
    assert( !Int32::IsPositive(-1) );

    assert(  Int32::IsZero(0) );
    assert( !Int32::IsZero(1) );
    assert( !Int32::IsZero(-1) );
}

void Parse()
{
    assert( Int32::Parse("32") == 32);
    assert( Int32::Parse("32 ") == 32); // Trailing whitespace does not matter
    
    // Leading whitespace matters... (Not allowed)
    try
    {
        std::int32_t result = Int32::Parse(" 32");

        UNUSED(result);
    }
    catch(const System::FormatException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }
    
    // Parsing an empty string...
    try
    {
        std::int32_t result = Int32::Parse("");

        UNUSED(result);
    }
    catch(const System::ArgumentNullException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }
    
    // Parsing a non-integer...
    try
    {
        std::int32_t result = Int32::Parse("salad");

        UNUSED(result);
    }
    catch(const System::FormatException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }
    
    // Parsing a float...
    try
    {
        // TODO: Is this proper behavior?
        std::int32_t result = Int32::Parse("3.14");

        assert( result == 3 );
    }
    catch (...)
    {
        assert(false);
    }
    
    // Parsing One Greater than Int32::MaxValue()
    try
    {
        std::int64_t max = Int32::MaxValue();
        std::string  max_plus_one{ std::format("{}", max + 1) };
        std::int32_t result = Int32::Parse( max_plus_one );

        UNUSED(result);
    }
    catch(const System::OverflowException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }

    // Parsing One Less than Int32::MinValue()
    try
    {
        std::int64_t min = Int32::MinValue();
        std::string  max_plus_one{ std::format("{}", min - 1) };
        std::int32_t result = Int32::Parse( max_plus_one );

        UNUSED(result);
    }
    catch(const System::OverflowException &e)
    {
        assert(true);
    }
    catch (...)
    {
        assert(false);
    }
}

void TryParse()
{
    {
        auto result = Int32::TryParse("32");

        assert( result.has_value() );
        assert( result.value() == 32 );
    }

    // Trailing whitespace does not matter
    {
        auto result = Int32::TryParse("32 ");

        assert( result );
        assert( result.has_value() );
        assert( result.value() == 32 );
    }
    
    // Leading whitespace matters... (Not allowed)
    {
        auto result = Int32::TryParse(" 32");

        assert( !result );
    }
    
    // Parsing an empty string...
    {
        auto result = Int32::TryParse("");

        assert( !result );
    }
    
    // Parsing a non-integer...
    {
        auto result = Int32::TryParse("salad");

        assert( !result );
    }
    
    // Parsing a float...
    {
        // TODO: Is this proper behavior?
        auto result = Int32::TryParse("3.14");

        // Gives us the number BEFORE the '.'
        assert( result );
        assert( result.value() == 3 );
    }
    
    // Parsing One Greater than Int32::MaxValue()
    {
        std::int64_t max = Int32::MaxValue();
        std::string  max_plus_one{ std::format("{}", max + 1) };
        auto result = Int32::TryParse( max_plus_one );

        assert( !result );
    }

    // Parsing One Less than Int32::MinValue()
    {
        std::int64_t min = Int32::MinValue();
        std::string  max_plus_one{ std::format("{}", min - 1) };
        auto result = Int32::TryParse( max_plus_one );

        assert( !result );
    }
}

void Addition()
{
    {
        Int32 b{ 5 };
        std::int32_t result = 3 + b;

        assert( result == 8 );
    }
    {
        Int32 b{ 5 };

        assert( 5 == b );
    }
}

void Run()
{
    DefaultConstructsToZero();
    ConstructingFromAConstantInteger();
    AutomaticConversionToStdInt32WhenCallingFunction();
    GetTypeCode();
    ToBoolean();
    ToByte();
    ToChar();
    ToInt16();
    ToInt32();
    ToSingle();
    ToDouble();
    ToString();
    Equality();
    TestINumberBase();
    Parse();
    TryParse();
    Addition();
}

}

int main(void)
{
    TestInt32::Run();
    return EXIT_SUCCESS;
}

import <cstdlib>;
import <cassert>;

import System.IO.StringWriter;

namespace TestStringWriter
{

template <class WriteType>
bool CheckWriter(WriteType input, std::string_view expected_output)
{
    System::IO::StringWriter writer;

    writer.Write( input );
    return writer.GetStringBuilder().ToString() == expected_output;
}

void DefaultConstructed()
{
    System::IO::StringWriter writer;

    assert( writer.GetStringBuilder().Length() == 0 );
}

void VerifyWrite()
{
    CheckWriter('a', "a");
    CheckWriter("This is a string", "This is a string");
    CheckWriter(false, "False");
    CheckWriter(true, "True");
    CheckWriter(0, "0"); // Weird case (0 is "special")
    CheckWriter(129, "129");
    CheckWriter(-328, "-328");
    CheckWriter( int8_t(8), "8" );
    CheckWriter( int8_t(-8), "-8" );
    CheckWriter( int16_t(32767), "32767" );
    CheckWriter( int16_t(-32768), "-32768" );
    CheckWriter( uint16_t(65535), "65535" );
    CheckWriter( float(3.2), "3.2" );
    CheckWriter( float(-32.3), "-32.3" );
    CheckWriter( double(3.2), "3.2" );
    CheckWriter( double(-32.3), "-32.3" );
}

void Run()
{
    DefaultConstructed();
    VerifyWrite();
}

}

int main(void)
{
    TestStringWriter::Run();
    return EXIT_SUCCESS;
}
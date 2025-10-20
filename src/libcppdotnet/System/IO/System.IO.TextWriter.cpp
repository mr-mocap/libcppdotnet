module System.IO.TextWriter;

import <cstdint>;
import <string_view>;

import System.Convert;

namespace System::IO
{

TextWriter::~TextWriter()
{
}

void TextWriter::Close()
{
}

void TextWriter::Flush()
{
}

void TextWriter::Write(bool value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(std::int16_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(std::uint16_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(std::int32_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(std::uint32_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(std::int64_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(std::uint64_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(float value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(double value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::WriteLine(std::string_view message)
{
    Write( message );
    Write( NewLine() );
}

void TextWriter::WriteLine(bool value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(char value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(int16_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(uint16_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(int32_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(uint32_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(int64_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(uint64_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(float value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(double value)
{
    Write( value );
    Write( NewLine() );
}

}

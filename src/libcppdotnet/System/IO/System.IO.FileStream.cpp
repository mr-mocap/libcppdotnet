module System.IO.FileStream;

import <ios>;
import <fstream>;
import <memory>;
import <string>;
import <string_view>;

import System.IO.FileMode;

namespace
{

std::ios_base::openmode MapMode(System::IO::FileMode mode)
{
    switch ( mode )
    {
    case System::IO::FileMode::CreateNew:
        return std::ios_base::out | std::ios_base::in | std::ios_base::trunc;

    case System::IO::FileMode::Create:
        return std::ios_base::out | std::ios_base::in;

    case System::IO::FileMode::Open:
    case System::IO::FileMode::OpenOrCreate:
        return std::ios_base::out | std::ios_base::in;

    case System::IO::FileMode::Truncate:
        return std::ios_base::out | std::ios_base::in | std::ios_base::trunc;

    case System::IO::FileMode::Append:
        return std::ios_base::in | std::ios_base::out | std::ios_base::app;
    }

    return std::ios_base::out | std::ios_base::in; // Shouldn't happen, but probably a decent default
}

std::fstream *AsFStream(std::iostream *input)
{
    return static_cast<std::fstream *>(input);
}

}

namespace System::IO
{

FileStream::FileStream(std::string_view filename)
    :
    Stream( std::make_unique<std::fstream>( std::string{filename} ), true, true, true )
{
}

FileStream::FileStream(std::string_view filename, const FileMode mode)
    :
    Stream( std::make_unique<std::fstream>( std::string{filename}, MapMode(mode) ), true, true, true )
{
}

FileStream::~FileStream()
{
    _stream.reset();
}

void FileStream::_close()
{
    if ( _stream )
    {
        AsFStream( _stream.get() )->close();
    }
}

}

module System.IO.ConsoleStream;

import <iostream>;

import System.IO.Stream;

namespace System::IO
{

ConsoleStream::ConsoleStream(Which which)
    :
    Stream{ Stream::ThisIsHereForStdMakeUnique{} },
    _which{ which }
{
    switch ( which )
    {
    case Which::In:
        _stream = std::make_unique<std::iostream>( std::cin.rdbuf() );
        _canRead = true;
        break;
    case Which::Out:
        _stream = std::make_unique<std::iostream>( std::cout.rdbuf() );
        _canWrite = true;
        break;
    case Which::Error:
        _stream = std::make_unique<std::iostream>( std::cerr.rdbuf() );
        _canWrite = true;
        break;
    case Which::Log:
        _stream = std::make_unique<std::iostream>( std::clog.rdbuf() );
        _canWrite = true;
        break;
    }
}

ConsoleStream::~ConsoleStream()
{
}

}

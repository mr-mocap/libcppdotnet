module System.Diagnostics.ConsoleTraceListener;

import <memory>;

import System.Diagnostics.TextWriterTraceListener;
import System.IO.ConsoleStream;



namespace System::Diagnostics
{

ConsoleTraceListener::ConsoleTraceListener()
    :
    TextWriterTraceListener( std::make_unique<System::IO::ConsoleStream>( System::IO::ConsoleStream::Out ) )
{
}

ConsoleTraceListener::ConsoleTraceListener(bool useErrorStream)
    :
    TextWriterTraceListener( std::make_unique<System::IO::ConsoleStream>( (useErrorStream) ?
                                                                                System::IO::ConsoleStream::Error :
                                                                                System::IO::ConsoleStream::Out ) )
{
}

ConsoleTraceListener::~ConsoleTraceListener()
{
}

}

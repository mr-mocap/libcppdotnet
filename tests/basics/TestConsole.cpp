import <cstdlib>;
import <string_view>;
import <cassert>;

import System.Console;
import System.IO.StreamReader;
import System.IO.StreamWriter;
import System.IO.StringReader;
import System.IO.StringWriter;

namespace TestConsole
{

void TestOut()
{
    System::Console::WriteLine("This is a line of text!");
    System::Console::WriteLine("Integer Value: {}", 42);
    System::Console::WriteLine("Here is a string: \"{}\"", "WaHoo!  We Did It!");

    System::Console::WriteLine("One Argument: {}", 1);
    System::Console::WriteLine("Two Arguments: {}, {}", 1, 2);
    System::Console::WriteLine("Three Arguments: {}, {}, {}", 1, 2, 3);
    System::Console::WriteLine("Four Arguments: {}, {}, {}, {}", 1, "two", 3.14159, "four");

    System::Console::Write("This is a line of text!");
    System::Console::Write( System::Console::Out().NewLine() );

    System::Console::Write("Integer Value: {}", 24);
    System::Console::Write( System::Console::Out().NewLine() );
    System::Console::WriteLine("Here is a string: \"{}\"", "WaHoo!  We Also Did It!");
    System::Console::Write( System::Console::Out().NewLine() );
}

void SetIn()
{
    std::string initial_data = "This is a line\nThe second line.";

    // It is NOT redirected initially
    assert( !System::Console::IsInputRedirected() );

    // We redirect it
    System::Console::SetIn( std::make_unique<System::IO::StringReader>(initial_data) );

    // And now it IS redirected
    assert( System::Console::IsInputRedirected() );

    System::Console::WriteLine( System::Console::ReadLine() );

    // Set it back to what it is by default
    System::Console::SetIn( std::make_unique<System::IO::StreamReader>(System::Console::OpenStandardInput()) );

    // And now it is NOT redirected
    assert( !System::Console::IsInputRedirected() );
}

void SetOut()
{
    // It is NOT redirected initially
    assert( !System::Console::IsOutputRedirected() );

    // We redirect it
    System::Console::SetOut( std::make_unique<System::IO::StringWriter>() );

    // And now it IS redirected
    assert( System::Console::IsOutputRedirected() );

    // Set it back to what it is by default
    System::Console::SetOut( std::make_unique<System::IO::StreamWriter>(System::Console::OpenStandardOutput()) );

    // And now it is NOT redirected
    assert( !System::Console::IsOutputRedirected() );
}

void SetError()
{
    // It is NOT redirected initially
    assert( !System::Console::IsErrorRedirected() );

    // We redirect it
    System::Console::SetError( std::make_unique<System::IO::StringWriter>() );

    // And now it IS redirected
    assert( System::Console::IsErrorRedirected() );

    // Set it back to what it is by default
    System::Console::SetError( std::make_unique<System::IO::StreamWriter>(System::Console::OpenStandardError()) );

    // And now it is NOT redirected
    assert( !System::Console::IsErrorRedirected() );
}

void Run()
{
    TestOut();
    SetIn();
    SetOut();
    SetError();
}

}

int main(void)
{
    TestConsole::Run();
    return EXIT_SUCCESS;
}

import <cstdlib>;
import <cassert>;

import System.Exception;
import System.Environment;
import System.Console;

namespace TestEnvironment
{

void GetEnvrionmentVariable()
{
    assert( System::Environment::GetEnvironmentVariable( "DISPLAY" ) == ":0" );
}

void SetEnvironmentVariable()
{
    assert( System::Environment::GetEnvironmentVariable( "MY_VAR" ).empty() );

    System::Environment::SetEnvironmentVariable( "MY_VAR", "22" );

    assert( System::Environment::GetEnvironmentVariable( "MY_VAR" ) == "22" );

    {
        bool threw = false;

        try
        {
            System::Environment::SetEnvironmentVariable( nullptr, nullptr );
        }
        catch(const System::Exception &e)
        {
            threw = true;
            std::string m( std::format("Message=\"{}\"\tTargetSite=\"{}\"", e.Message(), e.TargetSite()) );

            System::Console::Out().WriteLine( m );
        }
        assert( threw );
    }
}

void GetEnvironmentVariables()
{
    auto variables = System::Environment::GetEnvironmentVariables();
}

void Run()
{
    GetEnvrionmentVariable();
    SetEnvironmentVariable();
    GetEnvironmentVariables();
}
}

int main(void)
{
    TestEnvironment::Run();
    return EXIT_SUCCESS;
}
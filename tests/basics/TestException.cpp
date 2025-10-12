import <cstdlib>;
import <iostream>;
import <cassert>;

import System.Exception;

namespace TestException
{

void DefaultConstruction()
{
    System::ArgumentNullException e;

    assert( e.Message().empty() );
    assert( !e.InnerException() );
    assert( &e.GetBaseException() == &e );
}

void WithMessage()
{
    // Message Automatically filled in
    {
        System::ArgumentNullException ex{ "parameter" };

        assert( !ex.Message().empty() );
        assert( !ex.InnerException() );
        assert( &ex.GetBaseException() == &ex );
    }

    {
        auto msg = "Some kind of error occurred";
        System::ArgumentNullException ex{ "parameter", msg };

        assert( !ex.Message().empty() );
        assert( ex.Message() == msg );
        assert( ex.ParamName() == "parameter" );
        assert( !ex.InnerException() );
        assert( &ex.GetBaseException() == &ex );
    }
}


void WithMessageAndInnerException()
{
    auto msg = "Some Kind of Exception occurred";
    auto msg_outer = "This is the outer Exception";
    // Copy inner exception into outer
    {
        System::InvalidOperationException outer( msg_outer, System::ArgumentNullException( "field", msg ) );

        assert( !outer.Message().empty() );
        assert( outer.Message() == msg_outer );
        assert( outer.InnerException() );
        assert( &outer.GetBaseException() == outer.InnerException() );
        assert( outer.InnerException()->Message() == msg );

        //System::Console::WriteLine( outer.ToString() );
    }
}

void Run()
{
    DefaultConstruction();
    WithMessage();
    WithMessageAndInnerException();
}

}

int main(void)
{
    TestException::Run();
    return EXIT_SUCCESS;
}

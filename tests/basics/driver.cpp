import <iostream>;

import System;

int main ()
{
    System::OverflowException of("Some kind of overflow");

    std::cout << "Message = " << of.Message() << std::endl;
    std::cout << "ToString() = " << of.ToString() << std::endl;
    std::cout << "of.StackTrace() = " << of.StackTrace() << std::endl;
    return 0;
}

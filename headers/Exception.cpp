#include <iostream>
#include "Exception.h"

namespace mtm
{
    /*******************************/
    /*          Exception          */
    /*******************************/
    Exception::Exception() :
    header("Error: "), exception_name("Unknown Error") { }
    Exception::Exception(const std::string error) :
    header("Error: "), exception_name(error) { }
}
#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include <iostream>

namespace mtm
{
    class Exception : public std::exception
    {
    protected:
        std::string header;
        std::string exception_name;
    public:
        Exception();
        Exception(const std::string error);
        virtual ~Exception() = default;
    };
    class GraphException : public Exception {};
    class CalcException : public Exception {};
    class IllegalArgument : public GraphException
    { 
        std::string message;
    public:
        IllegalArgument();
        ~IllegalArgument() = default;
        const char* what() const noexcept override;
    };
}
#endif
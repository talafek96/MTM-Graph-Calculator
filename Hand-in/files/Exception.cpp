#include "Exception.h"

namespace mtm
{
    /*******************************/
    /*          Exception          */
    /*******************************/
    Exception::Exception() :
    header("Error: "), description("Unknown Error.") { }
    Exception::Exception(const std::string error) :
    header("Error: "), description(error) {}

    const char* IllegalBrackets::what() const noexcept
    {
        return message.c_str();
    }

    const char* CannotWriteToFile::what() const noexcept
    {
        return message.c_str();
    }

    const char* CannotReadFromFile::what() const noexcept
    {
        return message.c_str();
    }
    
    const char* FileIllegalVertexName::what() const noexcept
    {
        return message.c_str();
    }

    const char* FileDuplicateVertex::what() const noexcept
    {
        return message.c_str();
    }

    const char* FileInvalidEdge::what() const noexcept
    {
        return message.c_str();
    }

    const char* CorruptFile::what() const noexcept
    {
        return message.c_str();
    }

    const char* IllegalVertexName::what() const noexcept
    {
        return message.c_str();
    }

    const char* IllegalEdgeName::what() const noexcept
    {
        return message.c_str();
    }

    const char* IllegalComma::what() const noexcept
    {
        return message.c_str();
    }

    const char* IllegalGraphLiteral::what() const noexcept
    {
        return message.c_str();
    }

    const char* VertexSyntaxError::what() const noexcept
    {
        return message.c_str();
    }

    const char* EdgeSyntaxError::what() const noexcept
    {
        return message.c_str();
    }

    const char* VertexInEdgeDoesNotExist::what() const noexcept
    {
        return message.c_str();
    }
    
    const char* DuplicateVertex::what() const noexcept
    {
        return message.c_str();
    }

    const char* ParallelSelfEdgeDetected::what() const noexcept
    {
        return message.c_str();
    }

    const char* UnrecognizedCommand::what() const noexcept
    {
        return message.c_str();
    }

    const char* UndefinedVariable::what() const noexcept
    {
        return message.c_str();
    }

    const char* InvalidVariableName::what() const noexcept
    {
        return message.c_str();
    }

    const char* FunctionSyntaxError::what() const noexcept
    {
        return message.c_str();
    }

    const char* FunctionIllegalArgument::what() const noexcept
    {
        return message.c_str();
    }

    const char* FunctionIllegalFileName::what() const noexcept
    {
        return message.c_str();
    }
}
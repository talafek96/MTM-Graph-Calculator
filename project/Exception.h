#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include <iostream>
#include <string>

namespace mtm
{
    class Exception : public std::exception
    {
    protected:
        std::string header;
        std::string description;
    public:
        Exception();
        Exception(const std::string error);
        
        virtual ~Exception() = default;
    };

    class GraphException : public Exception 
    {
    public:
        GraphException();
        GraphException(const std::string error) :
        Exception(error) { }
        
        virtual ~GraphException() = default;
    };

    class CalcException : public Exception
    {
    public:
        CalcException();
        CalcException(const std::string error) :
        Exception(error) { }
        
        virtual ~CalcException() = default;
    };

    /*********************************/
    /*       Exception Classes       */
    /*********************************/

    class IllegalBrackets : public Exception
    { 
        std::string message;
    public:
        IllegalBrackets() : 
        Exception("Illegal brackets useage."), message(header += description) { }
        ~IllegalBrackets() = default;
        const char* what() const noexcept override;
    };

    class CannotWriteToFile : public Exception
    { 
        std::string message;
    public:
        CannotWriteToFile() :
        Exception("Cannot write to file."), message(header += description) { }
        CannotWriteToFile(const std::string& filename) : 
        Exception(std::string("Cannot write to the file ") + std::string("\"") + filename + 
        std::string("\".")), message(header += description) { }
        ~CannotWriteToFile() = default;
        const char* what() const noexcept override;
    };

    class CannotReadFromFile : public Exception
    { 
        std::string message;
    public:
        CannotReadFromFile() :
        Exception("Cannot read from file."), message(header += description) { }
        CannotReadFromFile(const std::string& filename) : 
        Exception(std::string("Cannot read from file ") + std::string("\"") + filename + std::string("\".")), 
        message(header += description) { }
        ~CannotReadFromFile() = default;
        const char* what() const noexcept override;
    };

    class FileIllegalVertexName : public Exception
    { 
        std::string message;
    public:
        FileIllegalVertexName() :
        Exception("The file contains an illegal vertex name."), message(header += description) { }
        FileIllegalVertexName(const std::string& vertex) : 
        Exception(std::string("The file contains an illegal vertex name - ") + std::string("\"") + vertex + 
        std::string("\".")), message(header += description) { }
        ~FileIllegalVertexName() = default;
        const char* what() const noexcept override;
    };

    class FileDuplicateVertex : public Exception
    { 
        std::string message;
    public:
        FileDuplicateVertex() :
        Exception("A duplicate vertex detected. All vertices must be unique."), message(header += description) { }
        FileDuplicateVertex(const std::string& vertex) : 
        Exception(std::string("The vertex ") + std::string("\"") + vertex + 
        std::string("\" appears more than once. All vertices must be unique.")), message(header += description) { }
        ~FileDuplicateVertex() = default;
        const char* what() const noexcept override;
    };
    
    class FileInvalidEdge : public Exception
    { 
        std::string message;
    public:
        FileInvalidEdge() : 
        Exception("The file contains an invalid edge."), message(header += description) { }
        FileInvalidEdge(const std::pair<std::string, std::string>& edge) : 
        Exception(std::string("The file contains an invalid edge - ") + 
        std::string("<") + edge.first + std::string(",") + edge.second + std::string(">.")),
         message(header += description) { }
        ~FileInvalidEdge() = default;
        const char* what() const noexcept override;
    };

    class CorruptFile : public Exception
    { 
        std::string message;
    public:
        CorruptFile() : 
        Exception("The file is corrupted or in wrong format and cannot be analyzed."), 
        message(header += description) { }
        ~CorruptFile() = default;
        const char* what() const noexcept override;
    };

    class IllegalVertexName : public GraphException
    { 
        std::string message;
    public:
        IllegalVertexName() : 
        GraphException("Illegal vertex name."), message(header += description) { }
        ~IllegalVertexName() = default;
        const char* what() const noexcept override;
    };

    class IllegalEdgeName : public GraphException
    { 
        std::string message;
    public:
        IllegalEdgeName() : 
        GraphException("Illegal edge name."), message(header += description) { }
        ~IllegalEdgeName() = default;
        const char* what() const noexcept override;
    };
    
    class IllegalComma : public GraphException
    { 
        std::string message;
    public:
        IllegalComma() : 
        GraphException("Illegal comma useage."), message(header += description) { }
        ~IllegalComma() = default;
        const char* what() const noexcept override;
    };
    
    class IllegalGraphLiteral : public GraphException
    { 
        std::string message;
    public:
        IllegalGraphLiteral() : 
        GraphException("Illegal graph literal."), message(header += description) { }
        ~IllegalGraphLiteral() = default;
        const char* what() const noexcept override;
    };
    
    class VertexSyntaxError : public GraphException
    { 
        std::string message;
    public:
        VertexSyntaxError() : 
        GraphException("Encountered a syntax error while processing the vertices."), 
        message(header += description) { }
        ~VertexSyntaxError() = default;
        const char* what() const noexcept override;
    };

    class EdgeSyntaxError : public GraphException
    { 
        std::string message;
    public:
        EdgeSyntaxError() : 
        GraphException("Encountered a syntax error while processing the edges."), 
        message(header += description) { }
        ~EdgeSyntaxError() = default;
        const char* what() const noexcept override;
    };
    
    class VertexInEdgeDoesNotExist : public GraphException
    { 
        std::string message;
    public:
        VertexInEdgeDoesNotExist() : 
        GraphException("An edge that has been entered contains a vertex that does not exist in the graph."), 
        message(header += description) { }
        ~VertexInEdgeDoesNotExist() = default;
        const char* what() const noexcept override;
    };

    class DuplicateVertex : public GraphException
    { 
        std::string message;
    public:
        DuplicateVertex() : 
        GraphException("Duplicate vertex was detected. All vertices must be unique."), 
        message(header += description) { }
        ~DuplicateVertex() = default;
        const char* what() const noexcept override;
    };
    
    class ParallelSelfEdgeDetected : public GraphException
    { 
        std::string message;
    public:
        ParallelSelfEdgeDetected() : 
        GraphException("Invalid edge. A parallel edge or a self loop was found."), 
        message(header += description) { }
        ~ParallelSelfEdgeDetected() = default;
        const char* what() const noexcept override;
    };

    class UnrecognizedCommand : public CalcException
    {
        std::string message;
    public:
        UnrecognizedCommand() :
        CalcException("Unrecognized command."), message(header += description) { }
        UnrecognizedCommand(const std::string& command) : 
        CalcException(std::string("Unrecognized command ") + std::string("\"") + command + 
        std::string("\".")), message(header += description) { }
        ~UnrecognizedCommand() = default;
        const char* what() const noexcept override;
    };

    class UndefinedVariable : public CalcException
    {
        std::string message;
    public:
        UndefinedVariable() :
        CalcException("Undefined variable detected."), message(header += description) { }
        UndefinedVariable(const std::string& variable) : 
        CalcException(std::string("Undefined variable ") + std::string("\"") + variable + 
        std::string("\".")), message(header += description) { }
        ~UndefinedVariable() = default;
        const char* what() const noexcept override;
    };

    class InvalidVariableName : public CalcException
    {
        std::string message;
    public:
        InvalidVariableName() :
        CalcException("Invalid variable name. All variables must begin with an alphabetic letter."), message(header += description) { }
        ~InvalidVariableName() = default;
        const char* what() const noexcept override;
    };

    class FunctionSyntaxError : public CalcException
    {
        std::string message;
    public:
        FunctionSyntaxError() :
        CalcException("Function syntax error."), message(header += description) { }
        FunctionSyntaxError(const std::string& function) : 
        CalcException(std::string("Function syntax error ") + std::string("\"") + function + 
        std::string("\".")), message(header += description) { }
        ~FunctionSyntaxError() = default;
        const char* what() const noexcept override;
    };

    class FunctionIllegalFileName : public CalcException
    {
        std::string message;
    public:
        FunctionIllegalFileName() :
        CalcException("Illegal file name was supplied."), message(header += description) { }
        FunctionIllegalFileName(const std::string& function) : 
        CalcException(std::string("Illegal file name was supplied in the function ") + std::string("\"") + function + 
        std::string("\".")), message(header += description) { }
        ~FunctionIllegalFileName() = default;
        const char* what() const noexcept override;
    };

    class FunctionIllegalArgument : public CalcException
    {
        std::string message;
    public:
        FunctionIllegalArgument() :
        CalcException("Illegal function argument."), message(header += description) { }
        FunctionIllegalArgument(const std::string& function) : 
        CalcException(std::string("Illegal argument found in the function ") + std::string("\"") + function + 
        std::string("\".")), message(header += description) { }
        ~FunctionIllegalArgument() = default;
        const char* what() const noexcept override;
    };
}
#endif
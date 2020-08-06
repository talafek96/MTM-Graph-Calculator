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
        CannotWriteToFile() = delete;
        CannotWriteToFile(const std::string& filename) : 
        Exception(("Cannot write to the file " + '"' + filename + "\".")), message(header += description) { }
        ~CannotWriteToFile() = default;
        const char* what() const noexcept override;
    };

    class CannotReadFromFile : public Exception
    { 
        std::string message;
    public:
        CannotReadFromFile() = delete;
        CannotReadFromFile(const std::string& filename) : 
        Exception(("Cannot write to the file " + '"' + filename + "\".")), message(header += description) { }
        ~CannotReadFromFile() = default;
        const char* what() const noexcept override;
    };

    class FileIllegalVertexName : public Exception
    { 
        std::string message;
    public:
        FileIllegalVertexName() = delete;
        FileIllegalVertexName(const std::string& vertex) : 
        Exception(("The file contains an illegal vertex name - " + '\"' + vertex + "\".")), message(header += description) { }
        ~FileIllegalVertexName() = default;
        const char* what() const noexcept override;
    };
    
    class FileInvalidEdge : public Exception
    { 
        std::string message;
    public:
        FileInvalidEdge() = delete;
        FileInvalidEdge(const std::pair<std::string, std::string>& edge) : 
        Exception(("The file contains an invalid edge - " + '<' + edge.first + ',' + edge.second + ">.")), message(header += description) { }
        ~FileInvalidEdge() = default;
        const char* what() const noexcept override;
    };

    class CorruptFile : public Exception
    { 
        std::string message;
    public:
        CorruptFile() : 
        Exception("The file is corrupted or in wrong format and cannot be analyzed."), message(header += description) { }
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
        GraphException("Encountered a syntax error while processing the vertices."), message(header += description) { }
        ~VertexSyntaxError() = default;
        const char* what() const noexcept override;
    };

    class EdgeSyntaxError : public GraphException
    { 
        std::string message;
    public:
        EdgeSyntaxError() : 
        GraphException("Encountered a syntax error while processing the edges."), message(header += description) { }
        ~EdgeSyntaxError() = default;
        const char* what() const noexcept override;
    };
    
    class VertexInEdgeDoesNotExist : public GraphException
    { 
        std::string message;
    public:
        VertexInEdgeDoesNotExist() : 
        GraphException("An edge that has been entered contains a vertex that does not exist in the graph."), message(header += description) { }
        ~VertexInEdgeDoesNotExist() = default;
        const char* what() const noexcept override;
    };
    
    class ParallelSelfEdgeDetected : public GraphException
    { 
        std::string message;
    public:
        ParallelSelfEdgeDetected() : 
        GraphException("Invalid edge. A parallel edge or a self loop was found."), message(header += description) { }
        ~ParallelSelfEdgeDetected() = default;
        const char* what() const noexcept override;
    };
}
#endif
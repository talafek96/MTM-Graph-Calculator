#ifndef GRAPH_LEXER_H
#define GRAPH_LEXER_H
#include "graph.h"
#include "Lexer.h"

namespace mtm
{
    class GraphLexer : public LexerClass
    {
    private:
        bool line_met;

        Token fetchNextVertexToken();
        Token fetchNextEdgeToken();
    public:
        GraphLexer() : 
        LexerClass(), line_met(false) { }

        GraphLexer(std::istream& stream) :
        LexerClass(stream), line_met(false) { }
        Token fetchNextToken() override;
    };

/*
    class VertexLexer : public GraphLexer
    {
    public:

    };

    class EdgeLexer : public GraphLexer
    {
    public:
        
    };
*/
}
#endif
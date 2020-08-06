#ifndef GRAPH_LEXER_H
#define GRAPH_LEXER_H
#include "Lexer.h"

namespace mtm
{
    class GraphLexer : public LexerClass
    {
    private:
        bool line_met;
        bool comma_met;

        Token fetchNextVertexToken();
        Token fetchNextEdgeToken();
    public:
        GraphLexer() : 
        LexerClass(), line_met(false), comma_met(false) { }

        GraphLexer(std::istream& stream) :
        LexerClass(stream), line_met(false) { }
        Token fetchNextToken() override;
        bool isLineMet() const;
    };
}
#endif
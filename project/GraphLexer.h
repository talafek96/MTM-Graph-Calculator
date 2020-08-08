#ifndef GRAPH_LEXER_H
#define GRAPH_LEXER_H
#include "Lexer.h"

namespace mtm
{
    class GraphLexer : public LexerClass
    {
    private:
        bool line_met = false;
        bool comma_met = false;

        Token fetchNextVertexToken();
        Token fetchNextEdgeToken();
    public:
        GraphLexer() = delete;
        GraphLexer(const std::string& str) :
        LexerClass(str), line_met(false), comma_met(false) { }

        Token fetchNextToken() override;
    };
}
#endif
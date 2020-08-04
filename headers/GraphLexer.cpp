#include "GraphLexer.h"
namespace mtm
{
    Token GraphLexer::fetchNextToken()
    {
        if(!line_met)
        {
            return fetchNextVertexToken();
        }
        return fetchNextEdgeToken();
    }

    Token GraphLexer::fetchNextVertexToken()
    {
        //lac = look-ahead-character
        char lac = NULL;

        //Get the next char from the stream
        getNextChar(lac);
    }
    
    Token GraphLexer::fetchNextEdgeToken()
    {
        //lac = look-ahead-character
        char lac = NULL;

        //Get the next char from the stream
        getNextChar(lac);
    }
}
#include "Lexer.h"
namespace mtm
{
    std::istream& LexerClass::getNextChar(char& c)
    {
        while(stream.get(c) && std::isspace(c));
        return stream;
    }

    Token& LexerClass::getCurrentToken()
    {
        return current_token;
    }
}
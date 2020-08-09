#include "Lexer.h"
namespace mtm
{
    const char LexerClass::getNextChar(char& c)
    {
        text_iterator++;
        while(std::isspace(text[text_iterator]))
        {
            text_iterator++;
        }
        c = text[text_iterator];
        return c;
    }

    Token& LexerClass::getCurrentToken()
    {
        return current_token;
    }
}
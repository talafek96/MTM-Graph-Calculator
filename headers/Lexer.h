#ifndef LEXER_H
#define LEXER_H
#include <stack>
#include <map>
#include <cctype>
#include "Exception.h"

namespace mtm
{
    //Classify the different token types
    enum class Type : char
    {
        end, eof = EOF, semicolon = ';', plus = '+',
        intersection = '^', diff = '-', product = '*',
        brac_open = '(', brac_close = ')',
        sbrac_open = '[', sbrac_close = ']',
        curl_open = '{', curl_close = '}',
        abrac_open = '<', abrac_close = '>',
        comp = '!', line = '|', comma = ',',
        variable = char(403), error
    };

    const std::string keywords[] = {
        "print", "delete", "who", "reset", "quit"
    };

    struct Token
    {
        Type type;
        std::string name;
        // Use stacks to ensure the weight of the brackets.
        std::stack<Type> brac_stack;
        std::stack<Type> sbrac_stack;
        std::stack<Type> curly_stack;
        // A bool variable is enough to determine proper
        // use of angular brackets.
        bool abrac_seen = false;
    };

    class LexerClass
    {
    protected:
        std::string text;
        int text_iterator;
        Token current_token;
    public:
        LexerClass() = delete;
        LexerClass(const std::string& str) : 
        text(str), text_iterator(-1) { }

        Token& getCurrentToken();
        virtual Token fetchNextToken() = 0;

        // Move the string up to the next non-whitespace char
        // and write it in c
        const char getNextChar(char& c);
    };
}
#endif
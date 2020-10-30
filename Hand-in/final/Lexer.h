#ifndef LEXER_H
#define LEXER_H
#include <stack>
#include <cctype>
#include "Exception.h"

#define TYPE_KEYWORDS_INDEX 399

namespace mtm
{
    //Classify the different token types
    enum class Type : char
    {
        end, semicolon = ';', plus = '+',
        intersection = '^', diff = '-', product = '*',
        brac_open = '(', brac_close = ')',
        sbrac_open = '[', sbrac_close = ']',
        curl_open = '{', curl_close = '}',
        abrac_open = '<', abrac_close = '>',
        comp = '!', line = '|', comma = ',', equal = '=',
        variable = char(TYPE_KEYWORDS_INDEX), file, graph_literal,
        rvalue_keyword, void_keyword, error
    };

    const std::string keywords[] = {
        "print", "save", "load", "delete", "who", "reset", "quit"
    };

    struct Token
    {
        Type type;
        std::string name;
        // Use stacks to ensure the weight of the brackets.
        std::stack<Type> brac_stack;
        std::stack<Type> sbrac_stack;
        // A bool variable is enough to determine proper
        // use of angular brackets/curly brackets.
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
#ifndef LEXER_H
#define LEXER_H
#include <stack>
#include <map>
#include <cctype>
#include "graph.h"
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
        variable, error
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

        // This map will only be used in the main parser.
        std::map<std::string, graph> graph_map;
    };

    class LexerClass
    {
    protected:
        std::istream& stream;
        Token current_token;
    public:
        LexerClass() : stream(std::cin) { }
        LexerClass(std::istream& stream) : stream(stream) { }

        Token& getCurrentToken();
        virtual Token fetchNextToken() = 0;

        // Move the stream up to the next non-whitespace char
        // and write it in c
        std::istream& getNextChar(char& c);
    };
}
#endif
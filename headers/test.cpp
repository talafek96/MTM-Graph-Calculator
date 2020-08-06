#include "GraphLexer.h"
#include "graph.h"
using namespace mtm;

void testGraphLexer()
{
    GraphLexer lexer;
    while(lexer.fetchNextToken().type != Type::end)
    {
        switch(lexer.getCurrentToken().type)
        {
            case Type::variable:
                std::cout << "Variable: " << lexer.getCurrentToken().name << std::endl;
                break;
            case Type::error:
                std::cout << "Syntax Error." << std::endl;
                break;
            default:
                std::cout << "Else: " << static_cast<char>(lexer.getCurrentToken().type)
                << std::endl;
                break;
        }
    }
}

int main()
{
    testGraphLexer();
    return 0;
}
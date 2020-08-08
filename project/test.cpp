#include "GraphClass.h"
using namespace mtm;

void testGraphLexer()
{
    GraphLexer lexer("a[;[];][] | <abc,c>");
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

void testGraphParser()
{
    std::string line;
    std::getline(std::cin, line);
    graph G;
    try
    {
        G = graph(line);
    }
    catch(const mtm::Exception& e)
    {
        std::cout << e.what() << '\n';
        return;
    }
    std::cout << "Legal graph literal! This is your graph:" << '\n'
    << G << '\n';
    graph::save(G, "graph.gc");
    graph G2 = graph::load("graph.gc");
    std::cout << std::endl << "This is the graph that was saved and loaded back:" << std::endl << G2;
}

int main()
{
    // testGraphLexer();
    testGraphParser();
    // graph G;
    // try
    // {
    //     G = graph::load("graph.gc");
    // }
    // catch(const mtm::Exception& e)
    // {
    //     std::cout << e.what() << '\n';
    //     return 1;
    // }
    // std::cout << "The graph that was loaded is: \n" << G;
    return 0;
}
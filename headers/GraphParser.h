#ifndef GRAPH_PARSER_H
#define GRAPH_PARSER_H
#include "GraphLexer.h"
#include "graph.h"

namespace mtm
{
    /*
        Recursive Descent Parse Tree

        // This is the root of the descent parse tree.
        evaluate:
            end (V) //EOS or EOF
            '|' (V)
            vertexList (V)
            vertexList '|' (V)
            vertexList '|' edgeList (V)
        
        vertexList: (function finishes at the next token)
            variable (V)
            vertexList ',' variable (V) // Left recursion.

        edgeList:
            edge (V)
            edgeList ',' edge (V) // Left recursion.
        
        edge:
            '<' variable ',' variable '>' (V)
    */
   class GraphParser
   {
    private:
        GraphLexer lexer;
        std::set<std::string> vertices;
        std::set<std::pair<std::string, std::string>> edges;
        friend class graph;

        void vertexList(bool get_next_token);
        void edgeList(bool get_next_token);
        void edge(bool get_next_token);
    public:
        explicit GraphParser(std::istream& stream) : lexer(stream) { }
        void evaluate();
   };
}
#endif
#ifndef CALC_PARSER_H
#define CALC_PARSER_H
#include "CalcLexer.h"
#include "GraphClass.h"
#include <map>

namespace mtm
{
    /*
        Recursive Descent Parse Tree

        // This is the root of the descent parse tree.
        evaluate:
            variable '=' rvalue end (V)
            void_keyword end (V) // Split by keywords (elaborated in the end of the tree)
        
        rvalue:
            term (V)
            rvalue '+' term (V)
            rvalue '-' term (V)
            rvalue '^' term (V)
            rvalue '*' term (V)
        
        term:
            variable (V)
            graph_literal (V)
            rvalue_keyword '(' file ')' (V) // "load" specific
            '!' term (V)
            '(' rvalue ')' (V)
        
        -----------------------------------

        Void Keywords - breakdown:

        "print":    void_keyword '(' rvalue ')' (V)
        "save":     void_keyword '(' rvalue ',' file ')' (V)
        "delete":   void_keyword '(' variable ')' (V)
        "reset":    void_keyword (V)
        "who":      void_keyword (V)
        "quit":     void_keyword (V)
    */
    class CalcParser
    {
    private:
        CalcLexer lexer;
        std::ostream* stream;
        bool quit_flag = false;
        bool save_flag = false;

        static std::map<std::string, graph> memory;

        graph term(bool get_next_token);
        graph rvalue(bool get_next_token);

    public:
        CalcParser() = delete;
        CalcParser(const std::string& str, std::ostream* stream) : 
        lexer(str), stream(stream) { }

        void evaluate();
        bool quitFlag() const;
    };
}
#endif
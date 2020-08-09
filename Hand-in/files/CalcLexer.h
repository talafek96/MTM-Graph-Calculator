#ifndef CALC_LEXER_H
#define CALC_LEXER_H
#include "Lexer.h"

namespace mtm
{
    class CalcLexer : public LexerClass
    {
    private:
        bool load_flag[2] = { false };
        bool save_flag[3] = { false };

        Token& updateFunctionFileArgument(const std::string& func_name);
    public:
        CalcLexer() = delete;
        CalcLexer(const std::string& str) :
        LexerClass(str) { }

        Token fetchNextToken() override;

        static bool isKeyword(const std::string& word);
        std::string getText() const;
    };
}
#endif
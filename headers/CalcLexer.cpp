#include "CalcLexer.h"
namespace mtm
{
    bool CalcLexer::isKeyword(const std::string& word)
    {
        int keywords_num = sizeof(keywords)/sizeof(*keywords);
        for(int i = 0; i < keywords_num; i++)
        {
            if(word == keywords[i])
            {
                return true;
            }
            return false;
        }
    }

    std::string CalcLexer::getText() const
    {
        return text;
    }

    Token& CalcLexer::updateFunctionFileArgument(const std::string& func_name)
    {
        current_token.name = text[text_iterator++];
        while(text[text_iterator] && text[text_iterator] != ')')
        {
            if(text[text_iterator] == '(' || text[text_iterator] == ',')
            {
                throw FunctionIllegalFileName(func_name);
            }
            current_token.name += text[text_iterator];
        }
        // text_iterator currently points to a ')' char, so we decrement it for
        // further token assessments.
        text_iterator--;

        // Cut the empty spaces in the file name:
        std::string whitespaces (" \t\f\v\n\r");

        std::size_t found = current_token.name.find_last_not_of(whitespaces);
        if (found!=std::string::npos)
        {
            current_token.name.erase(found+1);
        }
        return current_token;
    }

    Token CalcLexer::fetchNextToken()
    {
        //lac = look-ahead-character
        char lac = 0;

        //Get the next char from the string
        getNextChar(lac);
        if(load_flag[0] && lac != '(')
        {
            throw FunctionSyntaxError("load");
        }
        if(load_flag[1] && lac != ')')
        {
            if(lac == ',')
            {
                throw FunctionIllegalFileName("load");
            }
            updateFunctionFileArgument("load");
            current_token.type = Type::file;
            load_flag[1] = false;
            return current_token;
        }

        if(save_flag[0] && lac != '(')
        {
            throw FunctionSyntaxError("save");
        }
        if(save_flag[2] && lac != ')')
        {
            if(lac == ',')
            {
                throw FunctionIllegalFileName("save");
            }
            updateFunctionFileArgument("save");
            current_token.type = Type::file;
            save_flag[2] = false;
            return current_token;
        }
        // if(save_flag[1] && !std::isalpha(lac))
        // {
        //     throw FunctionIllegalArgument("save");
        // }
        // if(save_flag[2] && lac != ',')
        // {
        //     throw FunctionIllegalArgument();
        // }
        // if(save_flag[3] && lac != ')')
        // {

        // }

        switch(lac)
        {
            case '+': case '-': case '^': case '*': case '!': case '=':
            {
                current_token.type = static_cast<Type>(lac);
                return current_token;
            }
            case '{':
            {
                if(text.find('}', text_iterator) == std::string::npos)
                {
                    throw IllegalBrackets();
                }
                // Move the text iterator to the beginning of the graph literal
                // and start recording:
                current_token.name = text[++text_iterator];
                while(text[text_iterator] && text[text_iterator] != '}')
                {
                    // Record the current letter and increment the iterator.
                    current_token.name = text[text_iterator++];
                }
                // At this point, the text iterator points to '}', so
                // we increment it in order to "eat" it.
                text_iterator++;

                current_token.type = Type::graph_literal;
                return current_token;
            }
            case '(':
            {
                if(load_flag[0])
                {
                    load_flag[0] = false;
                    load_flag[1] = true; // load record flag
                    if(text.find(')', text_iterator) == std::string::npos)
                    {
                        throw FunctionSyntaxError("load");
                    }
                }
                else if(save_flag[0])
                {
                    save_flag[0] = false;
                    save_flag[1] = true; // Wait for the comma token
                }
                current_token.brac_stack.push(Type::brac_open);
                current_token.type = Type::brac_open;
                return current_token;
            }
            case ')':
            {
                if(current_token.brac_stack.empty())
                {
                    throw IllegalBrackets();
                }
                current_token.brac_stack.pop();
                current_token.type = Type::brac_close;
            }
            default:
            {
                if(std::isalpha(lac))
                {
                    current_token.name = lac;
                    while((lac = text[++text_iterator]) && std::isalnum(lac))
                    {
                        current_token.name += lac;
                    }
                    current_token.type = Type::variable;

                    // Check if the variable is actually a keyword:
                    if(isKeyword(current_token.name))
                    {
                        if(current_token.name == "load")
                        {
                            load_flag[0] = true; // Anticipate '('
                            current_token.type = Type::rvalue_keyword;
                        }
                        if(current_token.name == "save")
                        {
                            save_flag[0] = true; // Anticipate '('
                            current_token.type = Type::void_keyword;
                        }
                        if(current_token.name == "print"
                        || current_token.name == "delete"
                        || current_token.name == "reset"
                        || current_token.name == "who"
                        || current_token.name == "reset"
                        || current_token.name == "quit")
                        {
                            current_token.type = Type::void_keyword;
                        }
                    }
                }
                else if(lac == '\0' || lac == EOF || (std::isspace(lac) && !isblank(lac)))
                {
                    if(!current_token.brac_stack.empty())
                    {
                        throw IllegalBrackets();
                    }
                    current_token = { Type::end };
                }
                else if(lac == ',' && save_flag[1])
                {
                    save_flag[1] = false;
                    save_flag[2] = true; // save record flag
                    current_token.type = Type::comma;
                }
                else
                {
                    current_token.type = { Type::error };
                    throw UnrecognizedCommand(text);
                }
                return current_token;
            }
        }
    }
}
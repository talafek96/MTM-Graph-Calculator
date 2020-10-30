#include "CalcParser.h"

namespace mtm
{
    std::map<std::string, graph> CalcParser::memory;

    graph CalcParser::term(bool get_next_token)
    {
        if(get_next_token)
        {
            lexer.fetchNextToken();
        }
        switch (lexer.getCurrentToken().type)
        {
            case Type::variable:
            {
                if(!memory.count(lexer.getCurrentToken().name))
                {
                    throw UndefinedVariable(lexer.getCurrentToken().name);
                }
                graph& g = memory[lexer.getCurrentToken().name];
                lexer.fetchNextToken();
                return g;
            }

            case Type::graph_literal:
            {
                graph g(lexer.getCurrentToken().name);
                lexer.fetchNextToken();
                return g;
            }
            
            case Type::rvalue_keyword:
            {
                if(lexer.getCurrentToken().name == "load") // Sanity check
                {
                    if(lexer.fetchNextToken().type != Type::brac_open)
                    {
                        throw FunctionSyntaxError("load");
                    }
                    if(lexer.fetchNextToken().type != Type::file)
                    {
                        throw FunctionSyntaxError("load");
                    }
                    std::string filename = lexer.getCurrentToken().name;
                    if(lexer.fetchNextToken().type != Type::brac_close)
                    {
                        throw FunctionSyntaxError("load");
                    }
                    graph g = graph::load(filename);
                    lexer.fetchNextToken();
                    return g;
                }
                else
                {
                    throw Exception();
                }
                
            }

            case Type::comp:
            {
                return !term(true);
            }

            case Type::brac_open:
            {
                graph g = rvalue(true);
                if(lexer.getCurrentToken().type != Type::brac_close)
                {
                    throw UnrecognizedCommand();
                }
                lexer.fetchNextToken();
                return g;
            }

            default:
            {
                throw UnrecognizedCommand();
            }
        }
    } // End of term.

    graph CalcParser::rvalue(bool get_next_token)
    {
        graph g = term(get_next_token);
        while(lexer.getCurrentToken().type != Type::end)
        {
            switch(lexer.getCurrentToken().type)
            {
                case Type::plus: //G2*G3+G1
                {
                    g = g + term(true);
                    break;
                }

                case Type::diff:
                {
                    g = g - term(true);
                    break;
                }

                case Type::intersection:
                {
                    g = g ^ term(true);
                    break;
                }

                case Type::product:
                {
                    g = g * term(true);
                    break;
                }

                default:
                {
                    return g;
                }
            }
        }
        return g;
    } // End of rvalue.

    void CalcParser::evaluate()
    {
        lexer.fetchNextToken();
        switch(lexer.getCurrentToken().type)
        {
            case Type::variable:
            {
                std::string var = lexer.getCurrentToken().name;
                if(lexer.fetchNextToken().type != Type::equal)
                {
                    throw UnrecognizedCommand();
                }
                graph g = rvalue(true);
                if(lexer.getCurrentToken().type != Type::end)
                {
                    throw UnrecognizedCommand();
                }
                memory[var] = g;
                return;
            }

            case Type::void_keyword:
            {
                if(lexer.getCurrentToken().name == "print")
                {
                    if(lexer.fetchNextToken().type != Type::brac_open)
                    {
                        throw FunctionSyntaxError("print");
                    }
                    graph g = rvalue(true);
                    if(lexer.getCurrentToken().type != Type::brac_close)
                    {
                        throw FunctionSyntaxError("print");
                    }
                    if(lexer.fetchNextToken().type != Type::end)
                    {
                        throw UnrecognizedCommand();
                    }
                    *stream << g << std::endl;
                }
                else if(lexer.getCurrentToken().name == "save")
                {
                    if(lexer.fetchNextToken().type != Type::brac_open)
                    {
                        throw FunctionSyntaxError("save");
                    }
                    save_flag = true;
                    graph g = rvalue(true);
                    if(lexer.getCurrentToken().type != Type::comma)
                    {
                        throw FunctionSyntaxError("save");
                    }
                    std::string filename = lexer.fetchNextToken().name;
                    if(lexer.fetchNextToken().type != Type::brac_close)
                    {
                        throw FunctionSyntaxError("save");
                    }
                    if(lexer.fetchNextToken().type != Type::end)
                    {
                        throw UnrecognizedCommand();
                    }
                    graph::save(g, filename);
                }
                else if(lexer.getCurrentToken().name == "delete")
                {
                    if(lexer.fetchNextToken().type != Type::brac_open)
                    {
                        throw FunctionSyntaxError("delete");
                    }
                    std::string var = lexer.fetchNextToken().name;
                    if(lexer.fetchNextToken().type != Type::brac_close)
                    {
                        throw FunctionSyntaxError("delete");
                    }
                    if(lexer.fetchNextToken().type != Type::end)
                    {
                        throw UnrecognizedCommand();
                    }
                    if(memory.count(var) == 0)
                    {
                        throw UndefinedVariable(var);
                    }
                    memory.erase(var);
                }
                else if(lexer.getCurrentToken().name == "reset")
                {
                    if(lexer.fetchNextToken().type != Type::end)
                    {
                        throw UnrecognizedCommand();
                    }
                    memory.clear();
                }
                else if(lexer.getCurrentToken().name == "who")
                {
                    if(lexer.fetchNextToken().type != Type::end)
                    {
                        throw UnrecognizedCommand();
                    }
                    for(auto it = memory.begin(); it != memory.end(); it++)
                    {
                        *stream << it->first << std::endl;
                    }
                }
                else if(lexer.getCurrentToken().name == "quit")
                {
                    if(lexer.fetchNextToken().type != Type::end)
                    {
                        throw UnrecognizedCommand();
                    }
                    quit_flag = true;
                }
                else // Should never get here...
                {
                    throw UnrecognizedCommand();
                }
                return;
            }

            default:
            {
                throw UnrecognizedCommand();
            }
        }
    } // End of evaluate().

    bool CalcParser::quitFlag() const
    {
        return quit_flag;
    }
}
#include "CalcParser.h"

namespace mtm
{
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
                    throw UnrecognizedCommand(lexer.getText());
                }
                lexer.fetchNextToken();
                return g;
            }

            default:
            {
                throw UnrecognizedCommand(lexer.getText());
            }
        }
    } // End of term.

    graph CalcParser::rvalue(bool get_next_token)
    {
        graph g = term(get_next_token);
        if(lexer.getCurrentToken().type != Type::end)
        {
            switch(lexer.getCurrentToken().type)
            {
                case Type::plus:
                {
                    return g + rvalue(true);
                }

                case Type::diff:
                {
                    return g - rvalue(true);
                }

                case Type::intersection:
                {
                    return g ^ rvalue(true);
                }

                case Type::product:
                {
                    return g * rvalue(true);
                }

                default:
                {
                    throw UnrecognizedCommand(lexer.getText());
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
                    throw UnrecognizedCommand(lexer.getText());
                }
                graph g = rvalue(true);
                if(lexer.getCurrentToken().type != Type::end)
                {
                    throw UnrecognizedCommand(lexer.getText());
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
                    if(lexer.fetchNextToken().type != Type::brac_close)
                    {
                        throw FunctionSyntaxError("print");
                    }
                    if(lexer.fetchNextToken().type != Type::end)
                    {
                        throw UnrecognizedCommand(lexer.getText());
                    }
                    *stream << g;
                }
                else if(lexer.getCurrentToken().name == "save")
                {
                    if(lexer.fetchNextToken().type != Type::brac_open)
                    {
                        throw FunctionSyntaxError("save");
                    }
                    graph g = rvalue(true);
                    if(lexer.fetchNextToken().type != Type::comma)
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
                        throw UnrecognizedCommand(lexer.getText());
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
                        throw UnrecognizedCommand(lexer.getText());
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
                        throw UnrecognizedCommand(lexer.getText());
                    }
                    memory.clear();
                }
                else if(lexer.getCurrentToken().name == "who")
                {
                    if(lexer.fetchNextToken().type != Type::end)
                    {
                        throw UnrecognizedCommand(lexer.getText());
                    }
                    for(auto it = memory.begin(); it != memory.end(); it++)
                    {
                        *stream << it->first;

                        if(std::next(it) != memory.end())
                        {
                            *stream << std::endl;
                        }
                    }
                }
                else if(lexer.getCurrentToken().name == "quit")
                {
                    if(lexer.fetchNextToken().type != Type::end)
                    {
                        throw UnrecognizedCommand(lexer.getText());
                    }
                    quit_flag = true;
                }
                else // Should never get here...
                {
                    throw UnrecognizedCommand(lexer.getText());
                }
                return;
            }

            default:
            {
                throw UnrecognizedCommand(lexer.getText());
            }
        }
    }
}
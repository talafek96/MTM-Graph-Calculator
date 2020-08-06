#include "GraphLexer.h"
namespace mtm
{
    Token GraphLexer::fetchNextToken()
    {
        if(!line_met)
        {
            return fetchNextVertexToken();
        }
        return fetchNextEdgeToken();
    }

    Token GraphLexer::fetchNextVertexToken()
    {
        //lac = look-ahead-character
        char lac = 0;

        //Get the next char from the string
        getNextChar(lac);
        if(comma_met)
        {
            current_token.name.clear();
        }
        switch(lac)
        {
            case ',':
            {
                if(!current_token.sbrac_stack.empty())
                {
                    throw IllegalVertexName();
                }
                comma_met = true;
                current_token.type = Type::comma;
                return current_token;
            }
            case '|':
            {
                if(!current_token.sbrac_stack.empty())
                {
                    throw IllegalBrackets();
                }
                if(comma_met)
                {
                    throw IllegalComma();
                }
                line_met = true;
                current_token.type = Type::line;
                current_token.name.clear();
                return current_token;
            }
            default:
            {
                if(isalnum(lac) || lac == ';' || lac == '[' || lac == ']')
                {
                    comma_met = false;
                    if(lac == ']' || lac == ';')
                    {
                        throw IllegalVertexName();
                    }
                    current_token.name = lac;
                    if(lac == '[')
                    {
                        current_token.sbrac_stack.push(Type::sbrac_open);
                    }
                    while((lac = text[(++text_iterator)]) && 
                    (std::isalnum(lac) || lac == ';' || lac == '[' || lac == ']'))
                    {
                        switch(lac)
                        {
                            case ';':
                            {
                                if(current_token.sbrac_stack.empty())
                                {
                                    throw IllegalVertexName();
                                }
                                current_token.name += lac;
                                break;
                            }
                            case '[':
                            {
                                current_token.sbrac_stack.push(Type::sbrac_open);
                                current_token.name += lac;
                                break;
                            }
                            case ']':
                            {
                                if(current_token.sbrac_stack.empty())
                                {
                                    throw IllegalBrackets();
                                }
                                current_token.sbrac_stack.pop();
                                current_token.name += lac;
                                break;
                            }
                            default:
                                current_token.name += lac;
                                break;
                        }
                    }
                    /*
                     * At this point, lac is not a part of a variable anymore,
                     * so we have rewind the text iterator to make
                     * further assessments.
                     */
                    text_iterator--;
                    current_token.type = Type::variable;
                }
                else if(lac == 0 || lac == EOF || (isspace(lac) && !isblank(lac)))
                {
                    if(!current_token.sbrac_stack.empty())
                    {
                        throw IllegalBrackets();
                    }
                    if(comma_met)
                    {
                        throw IllegalComma();
                    }
                    current_token = { Type::end };
                }
                else
                {
                    current_token.type = Type::error;
                    current_token.name.clear();
                    throw IllegalVertexName();
                }
                return current_token;
            }
        }  
    } //End of fetchNextVertexToken
    
    Token GraphLexer::fetchNextEdgeToken()
    {
        //lac = look-ahead-character
        char lac = 0;

        //Get the next char from the string
        getNextChar(lac);
        switch(lac)
        {
            case ',':
            {
                if(!current_token.sbrac_stack.empty())
                {
                    throw IllegalEdgeName();
                }
                comma_met = true;
                current_token.type = Type::comma;
                return current_token;
            }
            case '<':
            {
                if(current_token.abrac_seen)
                {
                    throw IllegalEdgeName();
                }
                current_token.abrac_seen = true;
                comma_met = false;
                current_token.type = Type::abrac_open;
                return current_token;
            }
            case '>':
            {
                if(!current_token.abrac_seen)
                {
                    throw IllegalEdgeName();
                }
                if(comma_met)
                {
                    throw IllegalEdgeName();
                }
                current_token.abrac_seen = false;
                current_token.type = Type::abrac_close;
                return current_token;
            }
            default:
            {
                if(isalnum(lac) || lac == ';' || lac == '[' || lac == ']')
                {
                    comma_met = false;
                    if(lac == ']' || lac == ';')
                    {
                        throw IllegalVertexName();
                    }
                    current_token.name = lac;
                    if(lac == '[')
                    {
                        current_token.sbrac_stack.push(Type::sbrac_open);
                    }
                    while((lac = text[++text_iterator]) && 
                    (std::isalnum(lac) || lac == ';' || lac == '[' || lac == ']'))
                    {
                        switch(lac)
                        {
                            case ';':
                            {
                                if(current_token.sbrac_stack.empty())
                                {
                                    throw IllegalVertexName();
                                }
                                current_token.name += lac;
                                break;
                            }
                            case '[':
                            {
                                current_token.sbrac_stack.push(Type::sbrac_open);
                                current_token.name += lac;
                                break;
                            }
                            case ']':
                            {
                                if(current_token.sbrac_stack.empty())
                                {
                                    throw IllegalBrackets();
                                }
                                current_token.sbrac_stack.pop();
                                current_token.name += lac;
                                break;
                            }
                            default:
                                current_token.name += lac;
                                break;
                        }
                    }
                    /*
                     * At this point, lac is not a part of a variable anymore,
                     * so we have to rewind the text iterator to make
                     * further assessments.
                     */
                    text_iterator--;
                    current_token.type = Type::variable;
                }
                else if(lac == 0 || lac == EOF || (isspace(lac) && !isblank(lac)))
                {
                    if(!current_token.sbrac_stack.empty() || current_token.abrac_seen)
                    {
                        throw IllegalBrackets();
                    }
                    if(comma_met)
                    {
                        throw IllegalComma();
                    }
                    current_token = { Type::end };
                }
                else
                {
                    current_token.type = Type::error;
                    current_token.name.clear();
                    if(lac == '|')
                    {
                        throw IllegalGraphLiteral();
                    }
                    else
                    {
                        throw IllegalEdgeName();
                    }
                }
                return current_token;
            }
        }
    } // End of fetchNextEdgeToken

    bool GraphLexer::isLineMet() const
    {
        return line_met;
    }
}
#include "hilang.h"

bool Token::operator!=(const Token &other)
{
    return (value != other.value);
}

bool is_number(const std::string &tok)
{
    for (char c : tok)
    {
        if (!isdigit(c) && c != '.')
            return false;
    }
    return true;
}

bool is_bool(const std::string &tok)
{
    return (tok == "true" || tok == "false");
}

bool is_string(const std::string &tok)
{
    return (tok.front() == '"' && tok.back() == '"');
}

bool is_literal(const std::string &tok)
{
    return is_number(tok) || is_bool(tok) || is_string(tok);
}

bool is_name(const std::string &tok)
{
    for (char c : tok)
    {
        if (!isalpha(c) && !isdigit(c) && c != '_')
            return false;
    }

    return true;
}

TokenType token_type(Token tok)
{
    if (keywords.find(tok.value) != keywords.end())
        return ReservedName;
    if (tok.value.size() == 1)
    {
        if (operatorSymbols.find(tok.value[0]) != operatorSymbols.end())
            return Operator;
        if (punctuatorSymbols.find(tok.value[0]) != punctuatorSymbols.end())
            return Punctuator;
    }
    else if (tok.value.size() == 2)
    {
        if (operatorSymbolPairs.find(tok.value) != operatorSymbolPairs.end())
            return Operator;
    }

    if (tok.value[0] == '"' && tok.value.back() == '"')
        return Literal;

    if (is_number(tok.value))
        return Literal;

    if (is_name(tok.value))
        return Name;

    return UndefinedToken;
}

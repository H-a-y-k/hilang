#include "hilang.h"
#include <iostream>


bool is_bracket(char token)
{
    return token == '[' || token == ']';
}

bool is_parenthesis(char token)
{
    return token == '(' || token == ')';
}

bool is_brace(char token)
{
    return token == '{' || token == '}';
}

bool is_semicolon(char token)
{
    return token == ';';
}

bool is_punctuator(char symbol)
{
    return (punctuatorSymbols.find(symbol) != punctuatorSymbols.end());
}

bool is_keyword(const std::string &word)
{
    return (keywords.find(word) != keywords.end());
}

bool is_symbolPair(const std::string &word)
{
    return (operatorSymbolPairs.find(word) != operatorSymbolPairs.end());
}

bool is_discardable(char symbol)
{
    return (discardable.find(symbol) != discardable.end());
}

bool is_defined(const std::string &word)
{
    return !word.empty();
}

std::string extractNumber(const std::string &source, int current)
{
    std::string token;

    bool floating = false;

    for (int i = current; i < source.size(); i++)
    {
        if (!isdigit(source[i]) && source[i] != '.') break;

        if (isdigit(source[i]))
            token.push_back(source[i]);

        if (source[i] == '.')
        {
            if (floating == true)
                ;// error

            token.push_back(source[i]);
        }
    }
    return token;
}

std::string extractString(const std::string &source, int current)
{
    std::string token;

    bool escape = false;
    if (source[current] == '"' || source[current] == '\'')
    {
        token.push_back(source[current]);
        for (int i = current+1; i < source.size(); i++)
        {
            if ((source[i] == source[current]) && !escape) break;

            escape = (source[i] == '\\' && !escape);

            token.push_back(source[i]);
        }
        if (current + token.size() >= source.size() || source[current + token.size()] != source[current])
        {
            // error;
        }
        token.push_back(source[current]);
    }

    return token;
}

std::string extractName(const std::string &source, int current)
{
    std::string token;
    for (int i = current; i < source.size(); i++)
    {
        if (!isalpha(source[i]) && !isdigit(source[i]) && source[i] != '_')
            break;
        token.push_back(source[i]);
    }
    return token;
}

std::string extractText(const std::string &source, int current, int length)
{
    std::string token;
    int size = source.size();
    for (int i = current; i < std::min(current + length, size); i++)
        token += source[i];
    return token;
}

std::string extractBool(const std::string &source, int current)
{
    std::string token = extractName(source, current);
    if ((token == "true" || token == "false") && std::isspace(source[current + token.size()]))
        return token;
    return "";
}

std::string extractKeyword(const std::string &source, int current)
{
    std::string token = extractName(source, current);
    if (keywords.find(token) != keywords.end())
        return token;
    return "";
}

std::string extractSymbol(const std::string &source, int current)
{
    std::string token = extractText(source, current, 1);

    if (!token.empty() &&
            (operatorSymbols.find(token[0]) != operatorSymbols.end() ||
            (punctuatorSymbols.find(token[0]) != punctuatorSymbols.end())))
        return token;
    return "";
}

std::string extractSymbolPair(const std::string &source, int current)
{
    std::string token = extractText(source, current, 2);

    if (!token.empty() && operatorSymbolPairs.find(token) != operatorSymbolPairs.end())
        return token;
    return "";
}

Token extractToken(const std::string &source, int current)
{
    std::string token;
    TokenType type;

    token = extractNumber(source, current);
    if (token.empty()) token = extractString(source, current);
    if (token.empty()) token = extractBool(source, current);
    if (token.empty()) token = extractKeyword(source, current);
    if (token.empty()) token = extractName(source, current);
    if (token.empty()) token = extractSymbol(source, current);
    if (token.empty()) token = extractSymbolPair(source, current);

    return {token};
}

#include <map>

std::vector<Token> tokenize(const std::string &source)
{
    std::map<TokenType, std::string> mmm { {Literal, "Literal"}, {ReservedName, "Reserved"}, {Operator, "Operator"}, {Punctuator, "Punctuator"},
                                           {Name, "name"}, {UndefinedToken, "UndefinedToken"}};
    std::vector<Token> result;

    for (int i = 0; i < source.size();)
    {
        if (is_discardable(source[i]))
        {
            i++;
            continue;
        }
        Token token = extractToken(source, i);

//            std::cout << '<' << token.value << ", " << mmm[token_type(token)] << ">,";

        i += token.value.size();

        if (!token.value.empty())
        {
//            if (is_number(token.value))
//            {
//                std::string last = result[result.size()-1].value;
//                if (last == "+" || last == "-")
//                {
//                    if (result.size() > 1)
//                    {
//                        if ()
//                    }
//                    token.value = last + token.value;
//                }
//            }
            result.push_back(token);
        }
        else
            throw "error";
    }
    return result;
}

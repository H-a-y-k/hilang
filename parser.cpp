#include "hilang.h"
#include <algorithm>
#include <iostream>


bool is_operator(NonTerminal nt)
{
    return (std::find(_operator_seq.begin(), _operator_seq.end(), Word{nt}) != _operator_seq.end());
}

bool is_primitive(NonTerminal nt)
{
    return primitive.count(nt);
}

std::string expand(const std::vector<Token> toks)
{
    std::string result;
    for (const auto &tok : toks)
        result += tok.value;
    return result;
}

std::string parse_identifier(const std::vector<Token> &tokens, int &current)
{
    if (is_name(tokens[current].value))
    {
        return tokens[current].value;
    }
    return "";
}

std::string parse_literal(const std::vector<Token> &tokens, int &current)
{
    if (is_literal(tokens[current].value))
    {
        return tokens[current].value;
    }
    return "";
}

std::string match(const Word &word, const std::vector<Token> &tokens, int &current, const std::string &startstr)
{
    std::string expanded = startstr;
    std::string token_expanded = expanded;
    std::string tokentext;
    int current_start = current;

    if (current >= tokens.size())
    {
        return startstr;
    }
    for (auto symbol = word.begin(); symbol != word.end(); symbol++)
    {
        if (is_primitive(*symbol))
        {
            if (expanded+primitive[*symbol] == token_expanded+tokens[current].value)
            {
                expanded += primitive[*symbol];
                token_expanded += tokens.at(current).value;
                current++;
            }
            else
            {
                current = current_start;
                return startstr;
            }
        }
        else if (*symbol == _identifier)
        {
            auto id = parse_identifier(tokens, current);
            if (id.size())
            {
                expanded += id;
                token_expanded += id;
                current++;
            }
            else
            {
                current = current_start;
                return startstr;
            }
        }
        else if (*symbol == _literal)
        {
            auto lit = parse_literal(tokens, current);
            if (lit.size())
            {
                expanded += lit;
                token_expanded += lit;
                current++;
            }
            else
            {
                current = current_start;
                return startstr;
            }
        }
        else
        {
            auto expanded1 = match(rules[*symbol], std::vector<Token>(tokens.begin(), tokens.end()), current, expanded);
            if (expanded != expanded1)
            {
                expanded = expanded1;
                token_expanded = expanded;
            }
            else
            {
                current = current_start;
                return startstr;
            }
        }
    }

    std::cout << "/" << expanded << ".." << token_expanded << "/\n";
    if (expanded != token_expanded)
    {
        current = current_start;
        return startstr;
    }
    return expanded;
}

std::string match(const Sequence &seq, const std::vector<Token> &tokens, int &current, const std::string &startstr)
{
    for (const auto &word : seq)
    {
        auto m = match(word, tokens, current, startstr);
        if (m != startstr)
        {
            return m;
        }
    }
    return startstr;
}

// void parse(const std::vector<Token> &tokens)
// {
    
// }

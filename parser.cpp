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

std::string parse_primitive(const std::string &value, const std::vector<Token> &tokens, int &current)
{
    if (current >= tokens.size())
        return "";

    if (value == tokens[current].value)
    {
        current++;
        return value;
    }
    return "";
}

std::string parse_identifier(const std::vector<Token> &tokens, int &current)
{
    if (current >= tokens.size())
        return "";

    if (is_name(tokens[current].value))
    {
        std::string parsed = tokens[current].value;
        current++;
        return parsed;
    }
    return "";
}

std::string parse_literal(const std::vector<Token> &tokens, int &current)
{
    if (current >= tokens.size())
        return "";

    if (is_literal(tokens[current].value))
    {
        std::string parsed = tokens[current].value;
        current++;
        return parsed;
    }
    return "";
}

std::string parse_word(const Word &word, const std::vector<Token> &tokens, int &current)
{
    std::string parsed;
    std::string parsed_prev;

    int initial_index = current;

    if (current >= tokens.size())
        return "";

    for (auto symbol = word.begin(); symbol != word.end(); symbol++)
    {
        if (is_primitive(*symbol))
        {
            parsed += parse_primitive(primitive.at(*symbol), tokens, current);
        }
        else if (*symbol == _identifier)
        {
            parsed += parse_identifier(tokens, current);
        }
        else if (*symbol == _literal)
        {
            parsed += parse_literal(tokens, current);
        }
        else
        {
            parsed += parse_sequence(rules.at(*symbol), tokens, current);
        }

        if (parsed == parsed_prev)
        {
            current = initial_index;
            return "";
        }

        parsed_prev = parsed;
    }

//    std::cout << expanded << "\n";
    return parsed;
}

std::string parse_sequence(const Sequence &seq, const std::vector<Token> &tokens, int &current)
{
    for (const auto &word : seq)
    {
        auto parsed = parse_word(word, tokens, current);
        if (!parsed.empty())
        {
            return parsed;
        }
    }
    return "";
}

 void parse(const std::vector<Token> &tokens)
 {
     std::string parsed;
     int current = 0;
     do
     {
         parsed = parse_word(Word{_instruction}, tokens, current);
         std::cout << parsed << "\n";
     } while (!parsed.empty());
 }

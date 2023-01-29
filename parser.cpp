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


//std::string match(const Word &word, const std::vector<Token> &tokens, int &current, const std::string &startstr)
//{
//    std::string expanded = startstr;
//    std::string token_expanded = expanded;
//    std::string tokentext;
//    int current_start = current;

//    if (current >= tokens.size())
//    {
//        return startstr;
//    }
//    for (auto symbol = word.begin(); symbol != word.end(); symbol++)
//    {
//        if (is_primitive(*symbol))
//        {
//            if (expanded+primitive[*symbol] == token_expanded+tokens[current].value)
//            {
//                expanded += primitive[*symbol];
//                token_expanded += tokens.at(current).value;
//                current++;
//            }
//            else
//            {
//                current = current_start;
//                return startstr;
//            }
//        }
//        else if (*symbol == _identifier)
//        {
//            auto id = parse_identifier(tokens, current);
//            if (id.size())
//            {
//                expanded += id;
//                token_expanded += id;
//                current++;
//            }
//            else
//            {
//                current = current_start;
//                return startstr;
//            }
//        }
//        else if (*symbol == _literal)
//        {
//            auto lit = parse_literal(tokens, current);
//            if (lit.size())
//            {
//                expanded += lit;
//                token_expanded += lit;
//                current++;
//            }
//            else
//            {
//                current = current_start;
//                return startstr;
//            }
//        }
//        else
//        {
//            auto expanded1 = match(rules[*symbol], std::vector<Token>(tokens.begin(), tokens.end()), current, expanded);
//            if (expanded != expanded1)
//            {
//                expanded = expanded1;
//                token_expanded = expanded;
//            }
//            else
//            {
//                current = current_start;
//                return startstr;
//            }
//        }
//    }

//    std::cout << "/" << expanded << ".." << token_expanded << "/\n";
//    if (expanded != token_expanded)
//    {
//        current = current_start;
//        return startstr;
//    }
//    return expanded;
//}

std::string parse_primitive(const std::string &value, const std::vector<Token> &tokens, int &current, const std::string &initial_expansion)
{
    if (current >= tokens.size())
        return initial_expansion;

    if (value == tokens[current].value)
    {

        std::string parsed = initial_expansion + value;
        current++;
        return parsed;
    }
    return initial_expansion;
}

std::string parse_identifier(const std::vector<Token> &tokens, int &current, const std::string &initial_expansion)
{
    if (current >= tokens.size())
        return initial_expansion;

    if (is_name(tokens[current].value))
    {
        std::string parsed = initial_expansion + tokens[current].value;
        current++;
        return parsed;
    }
    return initial_expansion;
}

std::string parse_literal(const std::vector<Token> &tokens, int &current, const std::string &initial_expansion)
{
    if (current >= tokens.size())
        return initial_expansion;

    if (is_literal(tokens[current].value))
    {
        std::string parsed = initial_expansion + tokens[current].value;
        current++;
        return parsed;
    }
    return initial_expansion;
}

std::string parse_word(const Word &word, const std::vector<Token> &tokens, int &current, const std::string &initial_expansion)
{
    std::string expanded = initial_expansion;
    std::string parsed = expanded;

    int current_start = current;

    if (current >= tokens.size())
        return initial_expansion;

    for (auto symbol = word.begin(); symbol != word.end(); symbol++)
    {
        if (is_primitive(*symbol))
        {
            parsed = parse_primitive(primitive[*symbol], tokens, current, expanded);
        }
        else if (*symbol == _identifier)
        {
            parsed = parse_identifier(tokens, current, expanded);
        }
        else if (*symbol == _literal)
        {
            parsed = parse_literal(tokens, current, expanded);
        }
        else
        {
            parsed = parse_sequence(rules[*symbol], tokens, current, expanded);
        }

        if (expanded == parsed)
        {
            current = current_start;
            return initial_expansion;
        }

        expanded = parsed;
    }

    std::cout << "/" << expanded << "\n"; //token_expanded << "/\n";
    return expanded;
}

std::string parse_sequence(const Sequence &seq, const std::vector<Token> &tokens, int &current, const std::string &initial_expansion)
{
    for (const auto &word : seq)
    {
        auto parsed = parse_word(word, tokens, current, initial_expansion);
        if (parsed != initial_expansion)
        {
            return parsed;
        }
    }
    return initial_expansion;
}

// void parse(const std::vector<Token> &tokens)
// {
    
// }

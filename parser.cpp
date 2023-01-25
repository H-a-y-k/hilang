#include "hilang.h"
#include <algorithm>
#include <iostream>


bool is_operator(NonTerminal nt)
{
    return (std::find(_operator.begin(), _operator.end(), Word{nt}) != _operator.end());
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

std::string match(const Word &word, const std::vector<Token> &tokens, int &current, const std::string &startstr, const Sequence &this_seq)
{
    std::string expanded = startstr;
    std::string token_expanded;
    std::string tokentext;
    int current_start = current;

    for (auto symbol = word.begin(); symbol != word.end(); symbol++)
    {
        if (is_primitive(*symbol))
        {
            expanded += primitive[*symbol];
            if (expanded == token_expanded+tokens[current].value)
            {
                token_expanded += tokens[current].value;
                current++;
            }
            if (expanded.size() > (token_expanded + tokens[current].value).size())
                return "";
        }
        if (*symbol == __this)
        {
//            if (this_seq == Sequence{})
//                return match(word, tokens, current, expanded);
            return expanded + expand(match(this_seq, std::vector<Token>(tokens.begin(), tokens.begin() + current)));
        }
    }

    std::cout << expanded << ".." << token_expanded;
    if (expanded != token_expanded)
    {
        current = current_start;
        return "";
    }
    return expanded;
}

std::vector<Token> match(const Sequence &seq, const std::vector<Token> &tokens)
{
    int current = 0;
    for (const auto &word : seq)
    {
        if (!match(word, tokens, current, "", seq).empty())
            return std::vector<Token>(tokens.begin(), tokens.begin() + current);
    }
    return {};
}

//void parse(const std::vector<Token> &tokens)
//{

//}

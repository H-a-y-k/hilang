#ifndef HILANG
#define HILANG

#include <string>
#include <variant>
#include <set>
#include <vector>
#include <map>
#include "grammar.h"


bool is_bracket(char token);
bool is_parenthesis(char token);
bool is_brace(char token);
bool is_semicolon(char token);
bool is_punctuator(char symbol);
bool is_keyword(const std::string &word);
bool is_symbolPair(const std::string &word);
bool is_discardable(char symbol);
bool is_defined(const std::string &word);

enum TokenType
{
    Literal,
    Operator,
    Punctuator,
    Name,
    ReservedName,
    UndefinedToken
};

struct Token
{
    std::string value;

    bool operator != (const Token&);
};

inline const std::set<std::string> keywords = {"func", "return", "for", "int"};
inline const std::set<char> operatorSymbols = {'+', '-', '*', '/', '%', '=', '<', '>', '!', '&', '|', '^', '~'};
inline const std::set<char> punctuatorSymbols = {'(', ')', '[', ']', '{', '}', ';'};
inline const std::set<std::string> operatorSymbolPairs = {"++", "--", "+=", "-=", "*=", "/=", "%=", "<=", ">=", "==", "!=", "&&", "||", "<<", ">>"};
inline const std::set<char> discardable = {' ', '\n'};

//bool is_integer(Token tok);
//bool is_floating(Token tok);
bool is_number(const std::string &tok);
bool is_bool(const std::string &tok);
bool is_string(const std::string &tok);
bool is_literal(const std::string &tok);
bool is_name(const std::string &tok);

TokenType token_type(Token tok);
std::vector<Token> tokenize(const std::string &source);

std::string parse_identifier(const std::vector<Token>&, int&);
std::string parse_literal(const std::vector<Token>&, int&);
std::string match(const Word &word, const std::vector<Token>&, int&, const std::string& = "");
std::string match(const Sequence &seq, const std::vector<Token> &tokens, int &current, const std::string & = "");

#endif

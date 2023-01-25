#ifndef HILANG
#define HILANG

#include <string>
#include <variant>
#include <set>
#include <vector>
#include <map>

/*
 *  arg = empty | id | funcall
 *  arglist = arg | arg,Arglist
 *  funcall = id(arglist)
 * */

template <typename T>
std::vector<T> operator+(std::vector<T> const &x, std::vector<T> const &y)
{
    std::vector<T> vec;
    vec.reserve(x.size() + y.size());
    vec.insert(vec.end(), x.begin(), x.end());
    vec.insert(vec.end(), y.begin(), y.end());
    return vec;
}

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

const std::set<std::string> keywords = {"func", "return", "for", "int"};
const std::set<char> operatorSymbols = {'+', '-', '*', '/', '%', '=', '<', '>', '!', '&', '|', '^', '~'};
const std::set<char> punctuatorSymbols = {'(', ')', '[', ']', '{', '}', ';'};
const std::set<std::string> operatorSymbolPairs = {"++", "--", "+=", "-=", "*=", "/=", "%=", "<=", ">=", "==", "!=", "&&", "||", "<<", ">>"};
const std::set<char> discardable = {' ', '\n'};

//bool is_integer(Token tok);
//bool is_floating(Token tok);
bool is_number(const std::string &tok);
bool is_bool(const std::string &tok);
bool is_string(const std::string &tok);

TokenType token_type(Token tok);
std::vector<Token> tokenize(const std::string &source);

enum NonTerminal
{
    __empty, _plus, _minus, _mul, _div, _mod, _plusplus, _minusminus,
    _eq, _pluseq, _minuseq, _muleq, _diveq, _modeq,
    _lt, _gt, _lteq, _gteq, _eqeq, _neq,
    _bin_and, _bin_or, _xor, _neg, _ltlt, _gtgt,
    _and, _or, _not,
    _open_paren, _closed_paren, _open_bracket, _closed_bracket, _open_brace, _closed_brace, _semicolon, _comma,
    _int, _bool, _float, _string, _func, _return, _for,
    _identifier, _literal,
    _infix_operator,
    _argument,
    _arguments,
    _function_call,
    _expression,
    _lxh, _rxh,
};

inline std::map<NonTerminal, std::string> primitive {
    {__empty, ""},
    {_plus, "+"},
    {_minus, "-"},
    {_mul, "*"},
    {_div, "/"},
    {_mod, "%"},
    {_plusplus, "++"},
    {_minusminus, "--"},
    {_eq, "="},
    {_pluseq, "+="},
    {_minuseq, "-="},
    {_muleq, "*="},
    {_diveq, "/="},
    {_modeq, "%="},
    {_lt, "<"},
    {_gt, ">"},
    {_lteq, "<="},
    {_gteq, ">="},
    {_eqeq, "=="},
    {_neq, "!="},
    {_bin_and, "&"},
    {_bin_or, "|"},
    {_xor, "^"},
    {_neg, "~"},
    {_ltlt, "<<"},
    {_gtgt, ">>"},
    {_and, "&&"},
    {_or, "||"},
    {_not, {"!"}},
    {_open_paren, "("},
    {_closed_paren, ")"},
    {_open_bracket, "["},
    {_closed_bracket, "]"},
    {_open_brace, "{"},
    {_closed_brace, "}"},
    {_semicolon, ";"},
    {_comma, ","},
    {_int, "int"},
    {_bool, "bool"},
    {_float, "float"},
    {_string, "string"},
    {_func, "func"},
    {_return, "return"},
    {_for, "for"}
};

using Word = std::vector<NonTerminal>;
using Sequence = std::vector<Word>;

inline Sequence _arithmetic_operator = {{_plus}, {_minus}, {_mul}, {_div}, {_mod}, {_plusplus}, {_minusminus}};
inline Sequence _relation_operator = {{_lt}, {_gt}, {_lteq}, {_gteq}, {_eqeq}, {_neq}};
inline Sequence _assignment_operator = {{_eq}, {_pluseq}, {_minuseq}, {_muleq}, {_diveq}, {_modeq}};
inline Sequence _bitwise_operator = {{_bin_and}, {_bin_or}, {_xor}, {_neg}, {_ltlt}, {_gtgt}};
inline Sequence _logical_operator = {{_and}, {_or}, {_not}};

inline Sequence _prefix_operator = {{_not}, {_neg}, {_xor}, {_plusplus}, {_minusminus}};
inline Sequence _infix_operator_seq = {{_plus}, {_minus}, {_mul}, {_div}, {_mod}, {_lt}, {_gt}, {_lteq}, {_gteq}, {_eqeq}, {_eq}, {_pluseq}, {_minuseq}, {_muleq}, {_diveq}, {_modeq},
                           {_bin_and}, {_bin_or}, {_ltlt}, {_gtgt}, {_and}, {_or}};
inline Sequence _postfix_operator = {{_plusplus}, {_minusminus}};

inline Sequence _punctuator = {{_open_paren}, {_closed_paren}, {_open_bracket}, {_closed_bracket}, {_open_brace}, {_closed_brace}, {_semicolon}, {_comma}};
inline Sequence _keyword = {{_int}, {_bool}, {_float}, {_string}, {_func}, {_return}};
inline Sequence _operator = _prefix_operator + _infix_operator_seq + _postfix_operator;

inline std::map<NonTerminal, Sequence> rules {
    {   _infix_operator, _infix_operator_seq    },
    {   _argument, {{__empty}, {_identifier}, {_function_call}}    },
    {   _arguments, {{_argument}, {_argument, _comma}}   },
    {   _function_call, {{_identifier, _open_paren, _arguments, _closed_paren}}    },
    {   _lxh, {{_literal}, {_function_call}, {_identifier}}   },
    {   _rxh, {{_expression}, {_literal}, {_function_call}, {_identifier}}  },
    {   _expression, {{_lxh}, {_infix_operator}, {_rxh}}   }
};

std::string match(const Word &word, const std::vector<Token>&, int&, const std::string& = "", const Sequence &this_seq = {});
std::vector<Token> match(const Sequence &seq, const std::vector<Token> &tokens);

#endif

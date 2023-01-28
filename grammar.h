#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <map>
#include <string>
#include <vector>
#include "util.h"

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

inline Sequence _arithmetic_operator_seq = {{_plus}, {_minus}, {_mul}, {_div}, {_mod}, {_plusplus}, {_minusminus}};
inline Sequence _relation_operator_seq = {{_lt}, {_gt}, {_lteq}, {_gteq}, {_eqeq}, {_neq}};
inline Sequence _assignment_operator_seq = {{_eq}, {_pluseq}, {_minuseq}, {_muleq}, {_diveq}, {_modeq}};
inline Sequence _bitwise_operator_seq = {{_bin_and}, {_bin_or}, {_xor}, {_neg}, {_ltlt}, {_gtgt}};
inline Sequence _logical_operator_seq = {{_and}, {_or}, {_not}};

inline Sequence _prefix_operator_seq = {{_not}, {_neg}, {_xor}, {_plusplus}, {_minusminus}};
inline Sequence _postfix_operator_seq = {{_plusplus}, {_minusminus}};
inline Sequence _infix_operator_seq = {{_plus}, {_minus}, {_mul}, {_div}, {_mod}, {_lt}, {_gt}, {_lteq}, {_gteq}, {_eqeq}, {_eq}, {_pluseq}, {_minuseq}, {_muleq}, {_diveq}, {_modeq},
                           {_bin_and}, {_bin_or}, {_ltlt}, {_gtgt}, {_and}, {_or}};

inline Sequence _punctuator_seq = {{_open_paren}, {_closed_paren}, {_open_bracket}, {_closed_bracket}, {_open_brace}, {_closed_brace}, {_semicolon}, {_comma}};
inline Sequence _keyword_seq = {{_int}, {_bool}, {_float}, {_string}, {_func}, {_return}};
inline Sequence _operator_seq = _prefix_operator_seq + _infix_operator_seq + _postfix_operator_seq;

inline Sequence _argument_seq = {{__empty}, {_identifier}, {_function_call}};
inline Sequence _arguments_seq = {{_argument}, {_argument, _comma}};

inline Sequence _function_call_seq = {{_identifier, _open_paren, _arguments, _closed_paren}};
inline Sequence _lxh_seq = {{_literal}, {_function_call}, {_identifier}};
inline Sequence _rxh_seq = {{_expression}, {_literal}, {_function_call}, {_identifier}};

inline Sequence _expression_seq = {{_lxh, _infix_operator, _rxh}};

inline Sequence _instruction_seq = Sequence{{_expression}} + _punctuator_seq;

inline std::map<NonTerminal, Sequence> rules {
    {   _infix_operator, _infix_operator_seq    },
    {   _argument, _argument_seq   },
    {   _arguments, _arguments_seq   },
    {   _function_call, _function_call_seq },
    {   _lxh, _lxh_seq  },
    {   _rxh, _rxh_seq },
    {   _expression, _expression_seq }
};
#endif // GRAMMAR_H

#ifndef AST_H
#define AST_H

#include "hilang.h"

enum InstructionType
{
};

struct Instruction
{
    InstructionType type;
    std::vector<Token> tokens;
};

#endif // AST_H

#ifndef _OPERATOR_H
#define _OPERATOR_H

#include "token.h"

typedef enum OpType {
    OP_TYPE_UNARY,
    OP_TYPE_BINARY
} OperatorType;

typedef enum OpAssociativity {
    OP_ASSOC_LEFT,
    OP_ASSOC_RIGHT
} OpAssociativity;

typedef struct Operator {
    TokenType token;
    OpType type;
    OpAssociativity assoc;
} Operator;

#endif // _OPERATOR_H

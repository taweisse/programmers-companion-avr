#ifndef _EXPRESSION_H
#define _EXPRESSION_H

#include <stdbool.h>
#include <stdint.h>

typedef enum MathErr {
    MATH_ERR_OK = 0,
    MATH_ERR_DIV_BY_ZERO,
    MATH_ERR_OPERAND_NAN,
    MATH_ERR_PARENTHESIS_MISMATCH,
    MATH_ERR_INVALID_EXPR,
} MathErr;

typedef enum TokenType {
    TOK_LEFT_PARENTHESIS,
    TOK_RIGHT_PARENTHESIS,
    TOK_BITWISE_NOT,
    TOK_TIMES,
    TOK_DIVIVED_BY,
    TOK_MODULO,
    TOK_PLUS,
    TOK_MINUS,
    TOK_BITWISE_LEFT_SHIFT,
    TOK_BITWISE_RIGHT_SHIFT,
    TOK_BITWISE_AND,
    TOK_BITWISE_XOR,
    TOK_BITWISE_OR,
    TOK_INTEGER
} TokenType;

typedef struct Expression Expression;

Expression * expression_take_reference();
void expression_return_reference();

bool expression_append_operator(Expression *expr, TokenType tok);
bool expression_append_int(Expression *expr, uint64_t value);

bool expression_insert_operator(Expression *expr, TokenType tok, int pos);
bool expression_insert_int(Expression *expr, uint64_t value, int pos);

void expression_reset(Expression *expr);

bool expression_set_from_str(Expression *expr, const char *str);
bool expression_print(Expression *expr);

MathErr expression_evaluate(Expression *expr);

#endif
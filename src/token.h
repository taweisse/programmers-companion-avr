// Represents a token in an input expression.

#ifndef _NUMBER_H
#define _NUMBER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define VAL(tok_ref) ((tok_ref)->value.val)

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

typedef struct Token Token;

typedef enum MathErr {
    MATH_ERR_OK = 0,
    MATH_ERR_DIV_BY_ZERO,
    MATH_ERR_OPERAND_NAN,
    MATH_ERR_PARENTHESIS_MISMATCH
} MathErr;

Token * token_get_pool(size_t *pool_size);

void token_set_operator(Token *tok, TokenType type);
void token_set_integer(Token *tok, uint64_t val);
void token_reset(Token *tok);

MathErr tokens_add(const Token *tok1, const Token *tok2, Token *result);
MathErr tokens_sub(const Token *tok1, const Token *tok2, Token *result);
MathErr tokens_mul(const Token *tok1, const Token *tok2, Token *result);
MathErr tokens_div(const Token *tok1, const Token *tok2, Token *result);

bool token_to_str(Token *tok, char *buff, size_t buff_size);
const char * token_set_from_str(Token *tok, const char *buff);

#endif // _NUMBER_H

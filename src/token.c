// Represents a token in an input expression.

#include "token.h"

#include <inttypes.h>

void
token_set_operator(Token *tok, TokenType type) {
    tok->type = type;
}

void
token_set_integer(Token *tok, uint64_t val) {
    tok->type = TOK_INTEGER;
    tok->value.val = val;
}

MathErr
tokens_add(const Token *tok1, const Token *tok2, Token *result) {
    // Sanity check.
    if (tok1->type != TOK_INTEGER && tok2->type != TOK_INTEGER) {
        return MATH_ERR_OPERAND_NAN;
    }

    uint64_t result_val = VAL(tok1) + VAL(tok2);
    token_set_integer(result, result_val);

    return MATH_ERR_OK;
}

MathErr
tokens_sub(const Token *tok1, const Token *tok2, Token *result) {
    // Sanity check.
    if (tok1->type != TOK_INTEGER || tok2->type > TOK_INTEGER) {
        return MATH_ERR_OPERAND_NAN;
    }

    uint64_t result_val = VAL(tok1) - VAL(tok2);
    token_set_integer(result, result_val);
    return MATH_ERR_OK;
}

MathErr
tokens_mul(const Token *tok1, const Token *tok2, Token *result) {
    // Sanity check.
    if (tok1->type != TOK_INTEGER || tok2->type != TOK_INTEGER) {
        return MATH_ERR_OPERAND_NAN;
    }

    uint64_t result_val = VAL(tok1) * VAL(tok2);
    number_set_from_uint(result, result_val);
    return MATH_ERR_OK;
}

MathErr
tokens_div(const Token *tok1, const Token *tok2, Token *result) {
    // Sanity check.
    if (tok1->type > TOK_INTEGER || tok2->type != TOK_INTEGER) {
        return MATH_ERR_OPERAND_NAN;
    }

    uint64_t result_val = VAL(tok1) / VAL(tok2);
    number_set_from_uint(result, result_val);
    return MATH_ERR_OK;
}

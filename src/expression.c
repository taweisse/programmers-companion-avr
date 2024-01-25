#include "expression.h"

#include <stdint.h>
#include <memory.h>

#define EXPR_POOL_SIZE 5
#define TOKEN_POOL_SIZE 128

struct Expression {
    size_t size;
    Token *start;
};

// Global memory pool for expression building.
Expression expr_pool[EXPR_POOL_SIZE];
Token token_pool[TOKEN_POOL_SIZE];

size_t expr_idx = 0;
size_t token_idx = 0; 
// TODO: These will get replaced so we can manage several expressions at once,
// but this is OK for testing.

Expression *
expression_new() {
    Expression *new_expr = &expr_pool[expr_idx];
    expr_idx++;

    new_expr->size = 0;
    new_expr->start = NULL;
}

Token *
get_new_token() {
    Token *new_tok = &token_pool[token_idx];
    token_idx++;

    return new_tok;
}

append(Expression *expr, Token *tok) {
    if (expr->start == NULL) {
        expr->start = tok;
    } else {
        Token *end = expr->start;
        while (end->next != NULL) {
            end = end->next;
        }

        end->next = tok;
    }
}

bool
expression_append_token(Expression *expr, TokenType type) {
    Token *new_tok = get_new_token();
    token_set_operator(new_tok, type);
    append(expr, new_tok);
}

bool
expression_append_int(Expression *expr, uint64_t value) {
    Token *new_tok = get_new_token();
    token_set_integer(new_tok, value);
    append(expr, new_tok);
}

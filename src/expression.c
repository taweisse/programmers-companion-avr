#include "expression.h"

#include <stdint.h>
#include <memory.h>
#include <stdio.h>

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

bool expression_append_token(Expression *expr, Token *tok) {
    if (expr->start == NULL) {
        expr->start = tok;
    } else {
        Token *end = expr->start;
        while (end->next != NULL) {
            end = end->next;
        }

        end->next = tok;
    }

    return true; // TODO: Can this fail if we run out of free tokens?
}

bool
expression_append_operator(Expression *expr, TokenType type) {
    Token *new_tok = get_new_token();
    token_set_operator(new_tok, type);
    return expression_append_token(expr, new_tok);
}

bool
expression_append_int(Expression *expr, uint64_t value) {
    Token *new_tok = get_new_token();
    token_set_integer(new_tok, value);
    return expression_append_token(expr, new_tok);
}

void
expression_reset(Expression *expr) {
    memset(expr, 0, sizeof(Expression));
}

bool
expression_set_from_str(Expression *expr, const char *str) {
    // Reset the expression.
    expression_reset(expr);

    const char *cur_pos = str;
    int token_ct = 0;
    while (*cur_pos != '\0') {
        // Reset the token.
        token_reset(&token_pool[token_ct]);

        const char *new_pos = token_set_from_str(&token_pool[token_ct], cur_pos);
        if (new_pos == cur_pos) {
            // No characters were consumed, parse error!
            return false;
        }

        expression_append_token(expr, &token_pool[token_ct]);
        cur_pos = new_pos;
        token_ct += 1;
    }

    return true;
}

bool
expression_print(Expression *expr) {
    char buff[21]; // Large enough to hold UINT64_MAX.

    Token *cur_tok = expr->start;
    while (cur_tok != NULL) {
        if (! token_to_str(cur_tok, buff, sizeof(buff) / sizeof(buff[0]))) {
            return false;
        }
        fprintf(stdout, "%s ", buff);
        cur_tok = cur_tok->next;
    }

    fprintf(stdout, "\n");
    return true;
}

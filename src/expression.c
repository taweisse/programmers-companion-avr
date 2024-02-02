#include "expression.h"

#include <memory.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS_PER_EXPR 256

struct Expression {
    size_t size;
    Token tok_pool[MAX_TOKENS_PER_EXPR];
    Token *start;
    Token *end;
};

// Global expression reference.
Expression g_expr_ref;
bool g_ref_taken = false;

Expression *
expression_take_reference() {
    // Only one reference may be taken.
    if (g_ref_taken) {
        return NULL;
    }

    expression_reset(&g_expr_ref);
    g_ref_taken = true;
    return &g_expr_ref;
}

bool
expression_append_token(Expression *expr, Token *tok) {
    if (expr->start == NULL) {
        expr->start = tok;
        expr->end = expr->start;
    } else {
        tok->pre = expr->end;
        expr->end->next = tok;
        expr->end = tok;
    }

    expr->size += 1;
    return true;
}

bool
expression_append_operator(Expression *expr, TokenType type) {
    Token *new_tok = &expr->tok_pool[expr->size]; // TODO: Check size is within max.
    token_set_operator(new_tok, type);
    return expression_append_token(expr, new_tok);
}

bool
expression_append_int(Expression *expr, uint64_t value) {
    Token *new_tok = &expr->tok_pool[expr->size]; // TODO: Check size is within max.
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
    while (*cur_pos != '\0') {
        Token *new_tok = &expr->tok_pool[expr->size]; // TODO: Check size is within max.
        const char *new_pos = token_set_from_str(new_tok, cur_pos);
        if (new_pos == cur_pos) {
            // No characters were consumed, parse error!
            return false;
        }

        expression_append_token(expr, new_tok);
        cur_pos = new_pos;
    }

    return true;
}

bool
subexpression_print(const Token *start, const Token *end) {
    char buff[21]; // Large enough to hold UINT64_MAX.

    const Token *cur_tok = start;
    while (cur_tok != end) {
        if (! token_to_str(cur_tok, buff, sizeof(buff) / sizeof(buff[0]))) {
            return false;
        }
        fprintf(stdout, "%s ", buff);
        cur_tok = cur_tok->next;
    }

    fprintf(stdout, "\n");
    return true;
}

bool
expression_print(const Expression *expr) {
    subexpression_print(expr->start, NULL);
}

// Evaluates an expression from [start, end).
void
evaluate(Token *start, Token *end) {
    
}

MathErr
expression_evaluate(Expression *expr) {
    // Use a stack to evaluate atomic sub-expressions, I.E. parenthesis.
    Token *eval_stack[MAX_TOKENS_PER_EXPR + 1];
    size_t stack_idx = 0;

    Token *cur_tok = expr->start;
    while (cur_tok != NULL) {
        if (cur_tok->type == TOK_LEFT_PARENTHESIS) {
            // Push the start of the sub expression onto the stack.
            eval_stack[stack_idx] = cur_tok;
            stack_idx += 1;
        } else if (cur_tok->type == TOK_RIGHT_PARENTHESIS) {
            // Pop the most recent left parenthesis from the stack and evaluate
            // the sub expression.
            stack_idx -= 1;

            // If there is nothing left to pop, we have a parenthesis mismatch.
            if (stack_idx < 0) {
                return MATH_ERR_PARENTHESIS_MISMATCH;
            }

            // Remove left parenthesis.
            Token *start_paren = eval_stack[stack_idx];
            Token *start = start_paren->next;
            start->pre = start_paren->pre;

            if (start_paren->pre == NULL) {
                expr->start = start;
            } else {
                start->pre->next = start;
            }

            // Remove right parenthesis.
            Token *end = cur_tok->pre;

            // Can be NULL if there are empty parenthesis at the start of the
            // expression.
            if (end != NULL) {
                end->next = cur_tok->next;
            } else {
                expr->start = cur_tok->next;
            }

            // Can be NULL if closing parenthesis at the end of the expression.
            if (cur_tok->next != NULL) {
                cur_tok->next->pre = end;
            } else {
                expr->end = end;
            }

            // Calculate the partial tree for the sub expression.
            if (start < end) {
                evaluate(start, end->next);
            }
        }
    
        cur_tok = cur_tok->next;
    }

    // If there are any items in the stack once we reach the end of the
    // expression, we know there was a mismatched parenthesis.
    if (stack_idx > 0) {
        return MATH_ERR_PARENTHESIS_MISMATCH;
    }

    // Calculate the rest of the expression.
    evaluate(expr->start, NULL);

    return MATH_ERR_OK;
}

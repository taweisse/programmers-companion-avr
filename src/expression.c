#include "expression.h"

#include <memory.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS_PER_EXPR 256

//==============================================================================
// EXPRESSION TOKENS
//==============================================================================

typedef struct Token {
    struct Token *next;
    struct Token *pre;
    struct Token *left;
    struct Token *right;

    TokenType type;
    uint64_t value;
} Token;

// Note: str should be large enough to hold the maximum length string possible.
// 20 characters plus null terminator will safely represent UINT64_MAX.
bool
token_to_str(Token *tok, char *buff, size_t buff_size) {
    switch (tok->type) {
        case TOK_LEFT_PARENTHESIS: return 0 <= snprintf(buff, buff_size, "(");
        case TOK_RIGHT_PARENTHESIS: return 0 <= snprintf(buff, buff_size, ")");
        case TOK_BITWISE_NOT: return 0 <= snprintf(buff, buff_size, "~");
        case TOK_TIMES: return 0 <= snprintf(buff, buff_size, "*");
        case TOK_DIVIVED_BY: return 0 <= snprintf(buff, buff_size, "/");
        case TOK_MODULO: return 0 <= snprintf(buff, buff_size, "%");
        case TOK_PLUS: return 0 <= snprintf(buff, buff_size, "+");
        case TOK_MINUS: return 0 <= snprintf(buff, buff_size, "-");
        case TOK_BITWISE_LEFT_SHIFT: return 0 <= snprintf(buff, buff_size, "<<");
        case TOK_BITWISE_RIGHT_SHIFT: return 0 <= snprintf(buff, buff_size, ">>");
        case TOK_BITWISE_AND: return 0 <= snprintf(buff, buff_size, "&");
        case TOK_BITWISE_XOR: return 0 <= snprintf(buff, buff_size, "^");
        case TOK_BITWISE_OR: return 0 <= snprintf(buff, buff_size, "|");
        case TOK_INTEGER: return 0 <= snprintf(buff, buff_size, "%" PRIu64, tok->value);
    }
}

const char *
token_set_from_str(Token *tok, const char *buff) {
    switch (buff[0]) {
        case '(': {
            tok->type = TOK_LEFT_PARENTHESIS;
            return buff + 1;
        }

        case ')': {
            tok->type = TOK_RIGHT_PARENTHESIS;
            return buff + 1;
        }

        case '~': {
            tok->type = TOK_BITWISE_NOT;
            return buff + 1;
        }

        case '*': {
            tok->type = TOK_TIMES;
            return buff + 1;
        }

        case '/': {
            tok->type = TOK_DIVIVED_BY;
            return buff + 1;
        }
        
        case '%': {
            tok->type = TOK_MODULO;
            return buff + 1;
        }

        case '+': {
            tok->type = TOK_PLUS;
            return buff + 1;
        }
        
        case '-': {
            tok->type = TOK_MINUS;
            return buff + 1;
        }

        case '<': {
            if (buff[1] == '<') {
                tok->type = TOK_BITWISE_LEFT_SHIFT;
                return buff + 2;
            }
            return buff;
        }

        case '>': {
            if (buff[1] == '>') {
                tok->type = TOK_BITWISE_RIGHT_SHIFT;
                return buff + 2;
            }
            return buff;
        }

        case '&': {
            tok->type = TOK_BITWISE_AND;
            return buff + 1;
        }

        case '^': {
            tok->type = TOK_BITWISE_XOR;
            return buff + 1;
        }

        case '|': {
            tok->type = TOK_BITWISE_OR;
            return buff + 1;
        }

        default: {
            // Try to parse a number if no operators were found.
            int base = 10;
            const char *num_start = buff;

            // If the number starts with 0, it is either 0, or notation to represent
            // a binary, octal or hexadecimal number:
            //  * Binary numbers start with 0b, IE 0b1011
            //  * Octal numbers start with a leading 0, IE 0123
            //  * Hexadecimal numbers start with 0x, IE 0xA4
            if (buff[0] == '0') {
                if (buff[1] >= '0' && buff[1] <= '9') {
                    // If there are more numbers following the leading 0, we are in
                    // octal.
                    base = 8;
                    num_start = buff + 1;
                } else if ( buff[1] == 'x') {
                    // If the number starts with 0x, we are in hexadecimal.
                    base = 16;
                    num_start = buff + 2;
                } if (buff[1] == 'b') {
                    // If the number starts with 0b, we are in binary.
                    base = 2;
                    num_start = buff + 2;
                }
            }

            // Ensure that parsing big numbers will work on this hardware.
            assert(sizeof(unsigned long long) == sizeof(uint64_t));
            
            char *end_ptr;
            tok->value = strtoull(num_start, &end_ptr, base);
            tok->type = TOK_INTEGER;

            return end_ptr;
        }
    }
}

void
token_set_operator(Token *tok, TokenType type) {
    tok->type = type;
}

void
token_set_integer(Token *tok, uint64_t val) {
    tok->type = TOK_INTEGER;
    tok->value = val;
}

void
token_reset(Token *tok) {
    memset(tok, 0, sizeof(Token));
}

MathErr
tokens_add(const Token *tok1, const Token *tok2, Token *result) {
    // Sanity check.
    if (tok1->type != TOK_INTEGER || tok2->type > TOK_INTEGER) {
        return MATH_ERR_OPERAND_NAN;
    }

    uint64_t result_val = tok1->value + tok2->value;
    token_set_integer(result, result_val);

    return MATH_ERR_OK;
}

MathErr
tokens_sub(const Token *tok1, const Token *tok2, Token *result) {
    // Sanity check.
    if (tok1->type != TOK_INTEGER || tok2->type > TOK_INTEGER) {
        return MATH_ERR_OPERAND_NAN;
    }

    uint64_t result_val = tok1->value; - tok2->value;
    token_set_integer(result, result_val);
    return MATH_ERR_OK;
}

MathErr
tokens_mul(const Token *tok1, const Token *tok2, Token *result) {
    // Sanity check.
    if (tok1->type != TOK_INTEGER || tok2->type > TOK_INTEGER) {
        return MATH_ERR_OPERAND_NAN;
    }

    uint64_t result_val = tok1->value * tok2->value;
    token_set_integer(result, result_val);
    return MATH_ERR_OK;
}

MathErr
tokens_div(const Token *tok1, const Token *tok2, Token *result) {
    // Sanity check.
    if (tok1->type != TOK_INTEGER || tok2->type > TOK_INTEGER) {
        return MATH_ERR_OPERAND_NAN;
    }

    uint64_t result_val = tok1->value / tok2->value;
    token_set_integer(result, result_val);
    return MATH_ERR_OK;
}

//==============================================================================
// EXPRESSIONS
//==============================================================================

struct Expression {
    size_t size;
    Token tok_pool[MAX_TOKENS_PER_EXPR];
    Token *start;
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
    } else {
        Token *end = expr->start;
        while (end->next != NULL) {
            end = end->next;
        }

        end->next = tok;
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

            Token *start = eval_stack[stack_idx];
            // TODO: Calculate between start and cur_tok here! Dont forget to 
            //  remove parenthesis tokens first.
        }

        cur_tok = cur_tok->next;
    }

    // If there are any items in the stack once we reach the end of the
    // expression, we know there was a mismatched parenthesis.
    if (stack_idx > 0) {
        return MATH_ERR_PARENTHESIS_MISMATCH;
    }

    // TODO: Calculate the final result from the expression start to end.
}

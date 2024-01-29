#ifndef _EXPRESSION_H
#define _EXPRESSION_H

#include <stdbool.h>

#include "token.h"

typedef struct Expression Expression;

Expression *expression_new();

bool expression_append_token(Expression *expr, Token *tok);
bool expression_append_operator(Expression *expr, TokenType tok);
bool expression_append_int(Expression *expr, uint64_t value);

bool expression_insert_token(Expression *expr, TokenType tok, int pos);
bool expression_insert_int(Expression *expr, uint64_t value);

void expression_reset(Expression *expr);

bool expression_set_from_str(Expression *expr, const char *str);
bool expression_print(Expression *expr);

#endif
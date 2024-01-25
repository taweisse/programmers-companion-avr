#ifndef _EXPRESSION_H
#define _EXPRESSION_H

#include <stdbool.h>

#include "token.h"

typedef struct Expression Expression;

Expression *expression_new();

bool expression_append_token(Expression *exp, TokenType tok);
bool expression_append_int(Expression *exp, uint64_t value);

bool expression_insert_token(Expression *exp, TokenType tok, int pos);
bool expression_insert_int(Expression *exp, uint64_t value);

#endif
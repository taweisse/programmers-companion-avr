#ifndef _EXPRESSION_H
#define _EXPRESSION_H

#include <stdbool.h>
#include <stdint.h>

#include "error.h"
#include "token.h"

typedef struct Expression Expression;

Expression * expression_take_reference();
void expression_return_reference();

bool expression_append_operator(Expression *expr, TokenType tok);
bool expression_append_int(Expression *expr, uint64_t value);

bool expression_insert_operator(Expression *expr, TokenType tok, int pos);
bool expression_insert_int(Expression *expr, uint64_t value, int pos);

void expression_reset(Expression *expr);

bool expression_set_from_str(Expression *expr, const char *str);
bool expression_print(const Expression *expr);

MathErr expression_evaluate(Expression *expr);

#endif

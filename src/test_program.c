// Test program.

#include <stdio.h>

#include "expression.h"

int main(int argc, char *argv[]) {
    Expression *expr = expression_new();
    expression_append_int(expr, 24);
    expression_append_operator(expr, TOK_PLUS);
    expression_append_int(expr, 37);
    expression_print(expr);

    if (! expression_set_from_str(expr, "1+2+3*(5+2)")) {
        fprintf(stdout, "Expression parse error!\n");
    }
    expression_print(expr);
}

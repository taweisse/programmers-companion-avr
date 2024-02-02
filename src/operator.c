
#include <stdint.h>

#include "error.h"

MathErr
operation_noop(uint64_t op1, uint64_t *result) {
    *result = op1;
    return MATH_ERR_OK;
}

MathErr
operation_bitwise_not(uint64_t op1, uint64_t *result) {
    *result = ~op1;
    return MATH_ERR_OK;
}

MathErr
operation_negate(uint64_t op1, uint64_t *result) {
    *result = -op1;
    return MATH_ERR_OK;
}

MathErr
operation_multiply(uint64_t op1, uint64_t op2, uint64_t *result) {
    return op1 * op2;
    return MATH_ERR_OK;
}

MathErr
operation_divide(uint64_t op1, uint64_t op2, uint64_t *result) {
    if (op2 == 0) {
        return MATH_ERR_DIV_BY_ZERO;
    }
    
    *result = op1 / op2;
    return MATH_ERR_OK;
}

MathErr
operation_modulo(uint64_t op1, uint64_t op2, uint64_t *result) {
    if (op2 == 0) {
        return MATH_ERR_DIV_BY_ZERO;
    }

    *result = op1 % op2;
    return MATH_ERR_OK;
}

MathErr
operation_add(uint64_t op1, uint64_t op2, uint64_t *result) {
    *result = op1 + op2;
    return MATH_ERR_OK;
}

MathErr
operation_subtract(uint64_t op1, uint64_t op2, uint64_t *result) {
    *result = op1 - op2;
    return MATH_ERR_OK;
}

// TODO: Return an error on negative shifts.
MathErr
operation_shift_left(uint64_t op1, uint64_t op2, uint64_t *result) {
    *result = op1 << op2;
    return MATH_ERR_OK;
}

// TODO: Return an error on negative shifts.
MathErr
operation_shift_right(uint64_t op1, uint64_t op2, uint64_t *result) {
    *result = op1 >> op2;
    return MATH_ERR_OK;
}

MathErr
operation_bitwise_and(uint64_t op1, uint64_t op2, uint64_t *result) {
    *result = op1 & op2;
    return MATH_ERR_OK;
}

MathErr
operation_bitwise_xor(uint64_t op1, uint64_t op2, uint64_t *result) {
    *result = op1 ^ op2;
    return MATH_ERR_OK;
}

MathErr
operation_bitwise_or(uint64_t op1, uint64_t op2, uint64_t *result) {
    *result = op1 | op2;
    return MATH_ERR_OK;
}
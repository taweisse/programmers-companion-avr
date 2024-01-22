// Generic representation for numbers

#include "number.h"

#include <inttypes.h>

static inline uint64_t
size_cast(uint64_t num, SizeMode size_mode) {
    switch (size_mode) {
        case SIZE_MODE_BYTE: {
            return (uint8_t) num;
        }
        case SIZE_MODE_WORD: {
            return (uint16_t) num;
        }
        case SIZE_MODE_DWORD: {
            return (uint32_t) num;
        }
        case SIZE_MODE_QWORD: {
            return num;
        }
    }
}

void
number_set_from_uint(Number *num, uint64_t val) {
    // Set default size to QWORD, and test for smaller.
    SizeMode size = SIZE_MODE_QWORD;
    if (val <= UINT8_MAX) {
        size = SIZE_MODE_BYTE;
    } else if (val <= UINT16_MAX) {
        size = SIZE_MODE_WORD;
    } else if (val <= UINT32_MAX) {
        size = SIZE_MODE_DWORD;
    }

    num->type = TYPE_MODE_UNSIGNED;
    num->size = size;
    num->data.val = val;
}

void
number_set_from_int(Number *num, int64_t val) {
    // set default size to QWORD, and test for smaller.
    SizeMode size = SIZE_MODE_QWORD;
    if (INT8_MIN <= val && val <= INT8_MAX) {
        size = SIZE_MODE_BYTE;
    } else if (INT16_MIN <= val && val <= INT16_MAX) {
        size = SIZE_MODE_WORD;
    } else if (INT32_MIN <= val && val <= INT32_MAX) {
        size = SIZE_MODE_DWORD;
    }

    num->type = TYPE_MODE_SIGNED;
    num->size = size;
    num->data.val = (uint64_t) val;
}

MathErr
number_add(const Number *num1, const Number *num2, Number *res, SizeMode size_mode) {
    // Sanity check.
    if (num1->size > size_mode || num2->size > size_mode) {
        return MATH_ERR_SIZE_MISMATCH;
    }

    uint64_t result_val = size_cast(VAL(num1) + VAL(num2), size_mode);
    number_set_from_uint(res, result_val);
    return MATH_ERR_OK;
}

MathErr
number_sub(const Number *num1, const Number *num2, Number *res, SizeMode size_mode) {
    // Sanity check.
    if (num1->size > size_mode || num2->size > size_mode) {
        return MATH_ERR_SIZE_MISMATCH;
    }

    uint64_t result_val = size_cast(VAL(num1) - VAL(num2), size_mode);
    number_set_from_uint(res, result_val);
    return MATH_ERR_OK;
}

MathErr
number_mul(const Number *num1, const Number *num2, Number *res, SizeMode size_mode) {
    // Sanity check.
    if (num1->size > size_mode || num2->size > size_mode) {
        return MATH_ERR_SIZE_MISMATCH;
    }

    uint64_t result_val = size_cast(VAL(num1) * VAL(num2), size_mode);
    number_set_from_uint(res, result_val);
    return MATH_ERR_OK;
}

MathErr
number_div(const Number *num1, const Number *num2, Number *res, SizeMode size_mode) {
    // Sanity check.
    if (num1->size > size_mode || num2->size > size_mode) {
        return MATH_ERR_SIZE_MISMATCH;
    }

    uint64_t result_val = size_cast(VAL(num1) / VAL(num2), size_mode);
    number_set_from_uint(res, result_val);
    return MATH_ERR_OK;
}

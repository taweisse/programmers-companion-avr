// Generic representation for numbers

#ifndef _NUMBER_H
#define _NUMBER_H

#include <stdint.h>

#define VAL(num_ref) ((num_ref)->data.val)

typedef enum DisplayMode {
    DISPLAY_MODE_BIN = 2,
    DISPLAY_MODE_OCTAL = 8,
    DISPLAY_MODE_DECIMAL = 10,
    DISPLAY_MODE_HEX = 16
} DisplayMode;

typedef enum SizeMode {
    SIZE_MODE_BYTE = 8,
    SIZE_MODE_WORD = 16,
    SIZE_MODE_DWORD = 32,
    SIZE_MODE_QWORD = 64
} SizeMode;

typedef enum TypeMode {
    TYPE_MODE_UNSIGNED = 0,
    TYPE_MODE_SIGNED = 1
} TypeMode;

typedef enum MathErr {
    MATH_ERR_OK = 0,
    MATH_ERR_SIZE_MISMATCH
} MathErr;

typedef struct Number {
    TypeMode type;
    SizeMode size;

    union {
        uint64_t val;
        uint8_t bytes[8];
    } data;
} Number;

void number_set_from_uint(Number *num, uint64_t val);
void number_set_from_int(Number *num, int64_t val);

MathErr number_add(const Number *num1, const Number *num2, Number *res, SizeMode size_mode);
MathErr number_sub(const Number *num1, const Number *num2, Number *res, SizeMode size_mode);
MathErr number_mul(const Number *num1, const Number *num2, Number *res, SizeMode size_mode);
MathErr number_div(const Number *num1, const Number *num2, Number *res, SizeMode size_mode);

#endif // _NUMBER_H

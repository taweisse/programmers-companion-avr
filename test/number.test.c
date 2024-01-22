// Number tests.

#include "unity.h"
#include "number.h"
#include "inttypes.h"

void setUp() {}
void tearDown() {}

void unsigned_byte_arithmetic() {
    Number num21, num5, num250, result;
    number_set_from_uint(&num21, 21);
    number_set_from_uint(&num5, 5);
    number_set_from_uint(&num250, 250);

    // Test basic addition.
    number_add(&num21, &num5, &result, SIZE_MODE_BYTE);
    TEST_ASSERT_EQUAL_UINT8(21 + 5, VAL(&result));

    // Test addition resulting in an overflow.
    number_add(&num250, &num21, &result, SIZE_MODE_BYTE);
    TEST_ASSERT_EQUAL_UINT8(250 + 21, VAL(&result));

    // Test basic subtraction.
    number_sub(&num21, &num5, &result, SIZE_MODE_BYTE);
    TEST_ASSERT_EQUAL_UINT8(21 - 5, VAL(&result));

    // Test subtraction resulting in an underflow.
    number_sub(&num5, &num21, &result, SIZE_MODE_BYTE);
    TEST_ASSERT_EQUAL_UINT8(5 - 21, VAL(&result));

    // Test basic multiplication.
    number_mul(&num5, &num21, &result, SIZE_MODE_BYTE);
    TEST_ASSERT_EQUAL_UINT8(5 * 21, VAL(&result));

    // Test multiplication resulting in an overflow.
    number_mul(&num21, &num21, &result, SIZE_MODE_BYTE);
    TEST_ASSERT_EQUAL_UINT8(21 * 21, VAL(&result));

    // Test basic division.
    number_div(&num21, &num5, &result, SIZE_MODE_BYTE);
    TEST_ASSERT_EQUAL_UINT8(21 / 5, VAL(&result));
}

void unsigned_word_arithmetic() {
    uint16_t val20k = 20000, val10k = 10000, val60k = 60000;
    Number num20k, num10k, num60k, result;
    number_set_from_uint(&num20k, val20k);
    number_set_from_uint(&num10k, val10k);
    number_set_from_uint(&num60k, val60k);

    // Test basic addition.
    number_add(&num20k, &num10k, &result, SIZE_MODE_WORD);
    TEST_ASSERT_EQUAL_UINT16(val20k + val10k, VAL(&result));

    // Test addition resulting in an overflow.
    number_add(&num60k, &num20k, &result, SIZE_MODE_WORD);
    TEST_ASSERT_EQUAL_UINT16(val60k + val20k, VAL(&result));

    // Test basic subtraction.
    number_sub(&num20k, &num10k, &result, SIZE_MODE_WORD);
    TEST_ASSERT_EQUAL_UINT16(val20k - val10k, VAL(&result));

    // Test subtraction resulting in an underflow.
    number_sub(&num10k, &num20k, &result, SIZE_MODE_WORD);
    TEST_ASSERT_EQUAL_UINT16(val10k - val20k, VAL(&result));

    // Test basic multiplication.
    number_mul(&num10k, &num20k, &result, SIZE_MODE_WORD);
    TEST_ASSERT_EQUAL_UINT16(val10k * val20k, VAL(&result));

    // Test multiplication resulting in an overflow.
    number_mul(&num20k, &num20k, &result, SIZE_MODE_WORD);
    TEST_ASSERT_EQUAL_UINT16(val20k * val20k, VAL(&result));

    // Test basic division.
    number_div(&num20k, &num10k, &result, SIZE_MODE_WORD);
    TEST_ASSERT_EQUAL_UINT16(val20k / val10k, VAL(&result));
}

void unsigned_dword_arithmetic() {
    uint32_t val500mil = 500000000, val1mil = 1000000, val4bil = 4000000000;
    Number num500mil, num1mil, num4bil, result;
    number_set_from_uint(&num500mil, val500mil);
    number_set_from_uint(&num1mil, val1mil);
    number_set_from_uint(&num4bil, val4bil);

    // Test basic addition.
    number_add(&num500mil, &num1mil, &result, SIZE_MODE_DWORD);
    TEST_ASSERT_EQUAL_UINT32(val500mil + val1mil, VAL(&result));

    // Test addition resulting in an overflow.
    number_add(&num4bil, &num500mil, &result, SIZE_MODE_DWORD);
    TEST_ASSERT_EQUAL_UINT32(val4bil + val500mil, VAL(&result));

    // Test basic subtraction.
    number_sub(&num500mil, &num1mil, &result, SIZE_MODE_DWORD);
    TEST_ASSERT_EQUAL_UINT32(val500mil - val1mil, VAL(&result));

    // Test subtraction resulting in an underflow.
    number_sub(&num1mil, &num500mil, &result, SIZE_MODE_DWORD);
    TEST_ASSERT_EQUAL_UINT32(val1mil - val500mil, VAL(&result));

    // Test basic multiplication.
    number_mul(&num1mil, &num500mil, &result, SIZE_MODE_DWORD);
    TEST_ASSERT_EQUAL_UINT32(val1mil * val500mil, VAL(&result));

    // Test multiplication resulting in an overflow.
    number_mul(&num500mil, &num500mil, &result, SIZE_MODE_DWORD);
    TEST_ASSERT_EQUAL_UINT32(val500mil * val500mil, VAL(&result));

    // Test basic division.
    number_div(&num500mil, &num1mil, &result, SIZE_MODE_DWORD);
    TEST_ASSERT_EQUAL_UINT32(val500mil / val1mil, VAL(&result));
}

void unsigned_qword_arithmetic() {
    uint64_t val500quad = 500000000000000000, val100tril = 100000000000000, val18quint = 18000000000000000000u;
    Number num500quad, num100tril, num18quint, result;
    number_set_from_uint(&num500quad, val500quad);
    number_set_from_uint(&num100tril, val100tril);
    number_set_from_uint(&num18quint, val18quint);

    // Test basic addition.
    number_add(&num500quad, &num100tril, &result, SIZE_MODE_QWORD);
    TEST_ASSERT_EQUAL_UINT64(val500quad + val100tril, VAL(&result));

    // Test addition resulting in an overflow.
    number_add(&num18quint, &num500quad, &result, SIZE_MODE_QWORD);
    TEST_ASSERT_EQUAL_UINT64(val18quint + val500quad, VAL(&result));

    // Test basic subtraction.
    number_sub(&num500quad, &num100tril, &result, SIZE_MODE_QWORD);
    TEST_ASSERT_EQUAL_UINT64(val500quad - val100tril, VAL(&result));

    // Test subtraction resulting in an underflow.
    number_sub(&num100tril, &num500quad, &result, SIZE_MODE_QWORD);
    TEST_ASSERT_EQUAL_UINT64(val100tril - val500quad, VAL(&result));

    // Test basic multiplication.
    number_mul(&num100tril, &num500quad, &result, SIZE_MODE_QWORD);
    TEST_ASSERT_EQUAL_UINT64(val100tril * val500quad, VAL(&result));

    // Test multiplication resulting in an overflow.
    number_mul(&num500quad, &num500quad, &result, SIZE_MODE_QWORD);
    TEST_ASSERT_EQUAL_UINT64(val500quad * val500quad, VAL(&result));

    // Test basic division.
    number_div(&num500quad, &num100tril, &result, SIZE_MODE_QWORD);
    TEST_ASSERT_EQUAL_UINT64(val500quad / val100tril, VAL(&result));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(unsigned_byte_arithmetic);
    RUN_TEST(unsigned_word_arithmetic);
    RUN_TEST(unsigned_dword_arithmetic);
    RUN_TEST(unsigned_qword_arithmetic);

    return UNITY_END();
}

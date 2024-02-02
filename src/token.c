#include "token.h"

#include <inttypes.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// Note: str should be large enough to hold the maximum length string possible.
// 20 characters plus null terminator will safely represent UINT64_MAX.
bool
token_to_str(const Token *tok, char *buff, size_t buff_size) {
    switch (tok->type) {
        case TOK_LEFT_PARENTHESIS: return 0 <= snprintf(buff, buff_size, "(");
        case TOK_RIGHT_PARENTHESIS: return 0 <= snprintf(buff, buff_size, ")");
        case TOK_BITWISE_NOT: return 0 <= snprintf(buff, buff_size, "~");
        case TOK_TIMES: return 0 <= snprintf(buff, buff_size, "*");
        case TOK_DIVIDED_BY: return 0 <= snprintf(buff, buff_size, "/");
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
            tok->type = TOK_DIVIDED_BY;
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

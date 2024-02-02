
#ifndef _TOKEN_H
#define _TOKEN_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum TokenType {
    TOK_LEFT_PARENTHESIS,
    TOK_RIGHT_PARENTHESIS,
    TOK_BITWISE_NOT,
    TOK_TIMES,
    TOK_DIVIDED_BY,
    TOK_MODULO,
    TOK_PLUS,
    TOK_MINUS,
    TOK_BITWISE_LEFT_SHIFT,
    TOK_BITWISE_RIGHT_SHIFT,
    TOK_BITWISE_AND,
    TOK_BITWISE_XOR,
    TOK_BITWISE_OR,
    TOK_INTEGER
} TokenType;

// TODO: The below comment is probably wrong.

// Represents a single token of an expression. For example, in the expression
// 12 * (3 + 4), '12', '*', '(', '3', '+', '4', and ')' are the tokens which
// make it up. Each token has 4 connections to other tokens to form a graph. The
// graph is used to parse the expression tree for evaluation.
//
// Prior to parsing, the expression can be thought of as a bidirectional linked
// list of tokens. The *pre and *next pointers point to the previous and next
// token in the list, respectively. 
//
// During parsing, a binary tree is constructed in-place from the linked list
// using the *left and *right pointers, until we are left with a fully parsed
// expression tree ready for evaluation.
//
// The value field can be thought of as metadata whose information differs based
// on the token type. For TOK_INTEGER, this value is the literal numeric value
// of the integer that the token represents. However, for operator tokens, the
// value field holds a boolean (0 = false, 1 = true) indicating weather it can
// be treated as a value, IE if it has been previously parsed into a sub-tree.
typedef struct Token {
    struct Token *pre;
    struct Token *next;
    struct Token *left;
    struct Token *right;

    TokenType type;
    uint64_t value;
} Token;

// Note: buff should be large enough to hold the maximum length string possible.
// 20 characters plus null terminator will safely represent UINT64_MAX.
bool token_to_str(const Token *tok, char *buff, size_t buff_size);
const char * token_set_from_str(Token *tok, const char *buff);

void token_set_operator(Token *tok, TokenType type);
void token_set_integer(Token *tok, uint64_t val);

void token_reset(Token *tok);

#endif // _TOKEN_H

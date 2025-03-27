#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef enum {
    TOKEN_EOF,
    TOKEN_LET,
    TOKEN_PRINT,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_EQUALS,
    TOKEN_PLUS,
    TOKEN_SEMICOLON
} TokenType;

typedef struct {
    TokenType type;
    char text[64];
} Token;

typedef struct {
    Token tokens[1024];
    int count;
} TokenList;

TokenList lex(FILE *fp);

#endif
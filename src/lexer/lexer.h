#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef enum {
    TOKEN_EOF,
    TOKEN_LET,
    TOKEN_PRINT,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_EQUALS,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_SEMICOLON,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_GT,
    TOKEN_LT,
    TOKEN_EQ,
    TOKEN_NEQ,
    TOKEN_LTE,
    TOKEN_GTE, 
    TOKEN_LBRACE,
    TOKEN_RBRACE
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

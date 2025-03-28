#include "lexer.h"
#include <ctype.h>
#include <string.h>

TokenList lex(FILE *fp) {
    TokenList list = { .count = 0 };
    int c;

    while ((c = fgetc(fp)) != EOF) {
        Token token = {0};

        if (isspace(c)) continue;

        if (isalpha(c)) {
            char buffer[64] = {0};
            int i = 0;
            buffer[i++] = c;
            while ((c = fgetc(fp)) != EOF && isalnum(c)) {
                buffer[i++] = c;
            }
            ungetc(c, fp);

            if (strcmp(buffer, "let") == 0)
            token.type = TOKEN_LET;
            else if (strcmp(buffer, "print") == 0)
                token.type = TOKEN_PRINT;
            else if (strcmp(buffer, "if") == 0)
                token.type = TOKEN_IF;
            else if (strcmp(buffer, "else") == 0)
                token.type = TOKEN_ELSE; 
            else if (strcmp(buffer, "while") == 0)
                token.type = TOKEN_WHILE;
            else {
                token.type = TOKEN_IDENTIFIER;
                strcpy(token.text, buffer);
            }        

        } else if (isdigit(c)) {
            token.type = TOKEN_NUMBER;
            int i = 0;
            token.text[i++] = c;
            while ((c = fgetc(fp)) != EOF && isdigit(c)) {
                token.text[i++] = c;
            }
            ungetc(c, fp);

        } else if (c == '"') {
            char buffer[64] = {0};
            int i = 0;
            while ((c = fgetc(fp)) != EOF && c != '"') {
                buffer[i++] = c;
            }
        
            token.type = TOKEN_STRING;
            strcpy(token.text, buffer);
            list.tokens[list.count++] = token;
            continue;

        } else {
            if (c == '=' || c == '!' || c == '<' || c == '>') {
                int next = fgetc(fp);
                if (next == '=') {
                    switch (c) {
                        case '=': token.type = TOKEN_EQ; break;
                        case '!': token.type = TOKEN_NEQ; break;
                        case '<': token.type = TOKEN_LTE; break;
                        case '>': token.type = TOKEN_GTE; break;
                    }
                    list.tokens[list.count++] = token;
                    continue;
                } else {
                    ungetc(next, fp);
                }
            }
            
            switch (c) {
                case '=': token.type = TOKEN_EQUALS; break;
                case '+': token.type = TOKEN_PLUS; break;
                case '-': token.type = TOKEN_MINUS; break;
                case '*': token.type = TOKEN_MULTIPLY; break;
                case '/': token.type = TOKEN_DIVIDE; break;
                case ';': token.type = TOKEN_SEMICOLON; break;
                case '(': token.type = TOKEN_LPAREN; break;
                case ')': token.type = TOKEN_RPAREN; break;
                case '{': token.type = TOKEN_LBRACE; break;
                case '}': token.type = TOKEN_RBRACE; break;
                case '>': token.type = TOKEN_GT; break;
                case '<': token.type = TOKEN_LT; break;
                default: continue;
            }
        }

        list.tokens[list.count++] = token;
    }

    list.tokens[list.count++] = (Token){ .type = TOKEN_EOF };
    return list;
}
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

            if (strcmp(buffer, "let") == 0) token.type = TOKEN_LET;
            else if (strcmp(buffer, "print") == 0) token.type = TOKEN_PRINT;
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

        } else {
            switch (c) {
                case '=': token.type = TOKEN_EQUALS; break;
                case '+': token.type = TOKEN_PLUS; break;
                case ';': token.type = TOKEN_SEMICOLON; break;
                default: continue;
            }
        }

        list.tokens[list.count++] = token;
    }

    list.tokens[list.count++] = (Token){ .type = TOKEN_EOF };
    return list;
}
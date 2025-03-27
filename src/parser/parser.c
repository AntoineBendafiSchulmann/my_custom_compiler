#include "parser.h"
#include <stdlib.h>
#include <string.h>

static int pos = 0;
static TokenList *tokens_ptr;

static Token current() {
    return tokens_ptr->tokens[pos];
}

static void advance() {
    if (tokens_ptr->tokens[pos].type != TOKEN_EOF)
        pos++;
}

ASTNode* parse(TokenList *tokens) {
    tokens_ptr = tokens;
    pos = 0;
    ASTNode *head = NULL, *tail = NULL;

    while (current().type != TOKEN_EOF) {
        ASTNode *node = malloc(sizeof(ASTNode));
        node->next = NULL;

        if (current().type == TOKEN_LET) {
            node->type = AST_LET;
            advance();

            if (current().type == TOKEN_IDENTIFIER) {
                strcpy(node->name, current().text);
                advance();

                if (current().type == TOKEN_EQUALS) {
                    advance();
                    if (current().type == TOKEN_NUMBER) {
                        node->value = atoi(current().text);
                        advance();
                    }
                }
            }
        } else if (current().type == TOKEN_PRINT) {
            node->type = AST_PRINT;
            advance();

            if (current().type == TOKEN_IDENTIFIER) {
                strcpy(node->name, current().text);
                advance();
            }
        }

        if (current().type == TOKEN_SEMICOLON) advance();

        if (!head) head = node;
        else tail->next = node;
        tail = node;
    }

    return head;
}
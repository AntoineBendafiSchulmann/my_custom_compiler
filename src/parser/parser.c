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

Expr* parse_expression();

Expr* parse_factor() {
    Token tok = current();

    if (tok.type == TOKEN_LPAREN) {
        advance();
        Expr *expr = parse_expression();
        if (current().type == TOKEN_RPAREN) {
            advance();
            return expr;
        } else {
            fprintf(stderr, "[parser] Missing closing parenthesis\n");
            return NULL;
        }
    }

    advance();
    Expr *expr = malloc(sizeof(Expr));
    if (tok.type == TOKEN_NUMBER) {
        expr->type = EXPR_LITERAL;
        expr->value = atoi(tok.text);
    } else if (tok.type == TOKEN_STRING) {
        expr->type = EXPR_STRING;
        strcpy(expr->name, tok.text);
    } else if (tok.type == TOKEN_IDENTIFIER) {
        expr->type = EXPR_VARIABLE;
        strcpy(expr->name, tok.text);
    } else {
        free(expr);
        return NULL;
    }

    return expr;
}

Expr* parse_term() {
    Expr *left = parse_factor();

    while (current().type == TOKEN_MULTIPLY || current().type == TOKEN_DIVIDE) {
        char op = (current().type == TOKEN_MULTIPLY) ? '*' : '/';
        advance();

        Expr *right = parse_factor();

        Expr *expr = malloc(sizeof(Expr));
        expr->type = EXPR_BINARY;
        expr->binary.op = op;
        expr->binary.left = left;
        expr->binary.right = right;
        left = expr;
    }

    return left;
}

Expr* parse_expression() {
    Expr *left = parse_term();

    while (current().type == TOKEN_PLUS ||
    current().type == TOKEN_MINUS ||
    current().type == TOKEN_GT ||
    current().type == TOKEN_LT ||
    current().type == TOKEN_EQ ||
    current().type == TOKEN_NEQ ||
    current().type == TOKEN_LTE ||
    current().type == TOKEN_GTE) {

    char op;
    switch (current().type) {
        case TOKEN_PLUS:  op = '+'; break;
        case TOKEN_MINUS: op = '-'; break;
        case TOKEN_GT:    op = '>'; break;
        case TOKEN_LT:    op = '<'; break;
        case TOKEN_EQ:    op = '='; break;
        case TOKEN_NEQ:   op = '!'; break;
        case TOKEN_LTE:   op = 'l'; break;
        case TOKEN_GTE:   op = 'g'; break;
        default: return left;
    }
        advance();
        Expr *right = parse_term();

        Expr *expr = malloc(sizeof(Expr));
        expr->type = EXPR_BINARY;
        expr->binary.op = op;
        expr->binary.left = left;
        expr->binary.right = right;
        left = expr;
    }

    return left;
}

static ASTNode* parse_statement() {
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
                node->expr = parse_expression();
            }
        }

    } else if (current().type == TOKEN_IDENTIFIER &&
               tokens_ptr->tokens[pos + 1].type == TOKEN_EQUALS) {
        node->type = AST_ASSIGN;
        strcpy(node->name, current().text);
        advance();
        advance();
        node->expr = parse_expression();

    } else if (current().type == TOKEN_PRINT) {
        node->type = AST_PRINT;
        advance();
        node->expr = parse_expression();

    } else if (current().type == TOKEN_IF) {
        node->type = AST_IF;
        advance();

        if (current().type != TOKEN_LPAREN) {
            fprintf(stderr, "[parser] Expected '(' after if\n");
            return NULL;
        }

        advance();
        node->condition = parse_expression();

        if (current().type != TOKEN_RPAREN) {
            fprintf(stderr, "[parser] Expected ')' after condition\n");
            return NULL;
        }

        advance();

        if (current().type != TOKEN_LBRACE) {
            fprintf(stderr, "[parser] Expected '{' after if (...)\n");
            return NULL;
        }

        advance();
        ASTNode *body_head = NULL, *body_tail = NULL;

        while (current().type != TOKEN_RBRACE && current().type != TOKEN_EOF) {
            ASTNode *child = parse_statement();
            if (!child) break;

            if (!body_head) body_head = child;
            else body_tail->next = child;
            body_tail = child;
        }

        if (current().type != TOKEN_RBRACE) {
            fprintf(stderr, "[parser] Expected '}' to close if block\n");
            return NULL;
        }

        advance();
        node->body = body_head;

        if (current().type == TOKEN_ELSE) {
            advance();
            if (current().type != TOKEN_LBRACE) {
                fprintf(stderr, "[parser] Expected '{' after else\n");
                return NULL;
            }

            advance();
            ASTNode *else_head = NULL, *else_tail = NULL;

            while (current().type != TOKEN_RBRACE && current().type != TOKEN_EOF) {
                ASTNode *child = parse_statement();
                if (!child) break;

                if (!else_head) else_head = child;
                else else_tail->next = child;
                else_tail = child;
            }

            if (current().type != TOKEN_RBRACE) {
                fprintf(stderr, "[parser] Expected '}' to close else block\n");
                return NULL;
            }

            advance();
            node->else_body = else_head;
        }

    } else if (current().type == TOKEN_WHILE) {
        node->type = AST_WHILE;
        advance();

        if (current().type != TOKEN_LPAREN) {
            fprintf(stderr, "[parser] Expected '(' after while\n");
            return NULL;
        }

        advance();
        node->condition = parse_expression();

        if (current().type != TOKEN_RPAREN) {
            fprintf(stderr, "[parser] Expected ')' after while condition\n");
            return NULL;
        }

        advance();

        if (current().type != TOKEN_LBRACE) {
            fprintf(stderr, "[parser] Expected '{' after while (...)\n");
            return NULL;
        }

        advance();
        ASTNode *body_head = NULL, *body_tail = NULL;

        while (current().type != TOKEN_RBRACE && current().type != TOKEN_EOF) {
            ASTNode *child = parse_statement();
            if (!child) break;

            if (!body_head) body_head = child;
            else body_tail->next = child;
            body_tail = child;
        }

        if (current().type != TOKEN_RBRACE) {
            fprintf(stderr, "[parser] Expected '}' to close while block\n");
            return NULL;
        }

        advance();
        node->body = body_head;

    } else {
        fprintf(stderr, "[parser] Unexpected token: '%s' (type %d)\n",
                current().text, current().type);
        advance();
        free(node);
        return NULL;
    }

    if (current().type == TOKEN_SEMICOLON)
        advance();
    else if (node->type != AST_IF && node->type != AST_WHILE) {
        fprintf(stderr, "[parser] Missing semicolon.\n");
    }

    return node;
}

ASTNode* parse(TokenList *tokens) {
    tokens_ptr = tokens;
    pos = 0;
    ASTNode *head = NULL, *tail = NULL;

    while (current().type != TOKEN_EOF) {
        ASTNode *node = parse_statement();
        if (!node) break;

        if (!head) head = node;
        else tail->next = node;
        tail = node;
    }

    return head;
}

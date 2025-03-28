#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 256

static char symbol_table[MAX_SYMBOLS][64];
static int symbol_count = 0;

static int symbol_exists(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i], name) == 0)
            return 1;
    }
    return 0;
}

static void symbol_add(const char *name) {
    if (symbol_count < MAX_SYMBOLS) {
        strcpy(symbol_table[symbol_count++], name);
    }
}

static void check_expr(Expr *expr) {
    if (!expr) return;

    switch (expr->type) {
        case EXPR_LITERAL:
            break;
        case EXPR_STRING: 
            break;
        case EXPR_VARIABLE:
            if (!symbol_exists(expr->name)) {
                fprintf(stderr, "[semantic] Undefined variable: %s\n", expr->name);
                exit(1);
            }
            break;
        case EXPR_BINARY:
            check_expr(expr->binary.left);
            check_expr(expr->binary.right);
            break;
    }
}

int semantic_check(ASTNode *ast) {
    symbol_count = 0;

    for (ASTNode *node = ast; node != NULL; node = node->next) {
        if (node->type == AST_LET) {
            check_expr(node->expr);
            symbol_add(node->name);
        } else if (node->type == AST_PRINT) {
            check_expr(node->expr);
        }
    }

    return 0;
}
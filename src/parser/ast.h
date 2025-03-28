#ifndef AST_H
#define AST_H

typedef enum {
    AST_LET,
    AST_ASSIGN,
    AST_PRINT,
    AST_IF,
    AST_WHILE
} ASTType;

typedef enum {
    EXPR_LITERAL,
    EXPR_VARIABLE,
    EXPR_BINARY,
    EXPR_STRING
} ExprType;

typedef struct Expr {
    ExprType type;
    union {
        int value;
        char name[64];
        struct {
            char op;
            struct Expr *left;
            struct Expr *right;
        } binary;
    };
} Expr;

typedef struct ASTNode {
    ASTType type;

    char name[64];
    Expr *expr;

    Expr *condition;
    struct ASTNode *body;
    struct ASTNode *else_body;

    struct ASTNode *next;
} ASTNode;

void free_ast(ASTNode *node);

#endif

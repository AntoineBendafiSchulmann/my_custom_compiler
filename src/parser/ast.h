#ifndef AST_H
#define AST_H

typedef enum {
    AST_LET,
    AST_PRINT
} ASTType;

typedef struct ASTNode {
    ASTType type;
    char name[64];
    int value;
    struct ASTNode *next;
} ASTNode;

void free_ast(ASTNode *node);

#endif
#include "ast.h"
#include <stdlib.h>

void free_ast(ASTNode *node) {
    while (node) {
        ASTNode *next = node->next;
        free(node);
        node = next;
    }
}
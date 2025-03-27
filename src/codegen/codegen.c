#include "codegen.h"

void generate_code(ASTNode *root, FILE *out) {
    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "int main() {\n");

    for (ASTNode *node = root; node; node = node->next) {
        if (node->type == AST_LET) {
            fprintf(out, "    int %s = %d;\n", node->name, node->value);
        } else if (node->type == AST_PRINT) {
            fprintf(out, "    printf(\"%%d\\n\", %s);\n", node->name);
        }
    }

    fprintf(out, "    return 0;\n");
    fprintf(out, "}\n");
}

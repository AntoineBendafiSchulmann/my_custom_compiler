#include "codegen.h"
#include <stdio.h>

static void emit_expression(FILE *out, Expr *expr);
static void generate_code_internal(ASTNode *root, FILE *out, int in_block);

void generate_code(ASTNode *root, FILE *out) {
    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "int main() {\n");
    generate_code_internal(root, out, 0);
    fprintf(out, "    return 0;\n");
    fprintf(out, "}\n");
}

static void generate_code_internal(ASTNode *root, FILE *out, int in_block) {
    (void) in_block;

    for (ASTNode *node = root; node; node = node->next) {
        if (node->type == AST_LET) {
            fprintf(out, "    int %s = ", node->name);
            emit_expression(out, node->expr);
            fprintf(out, ";\n");

        } else if (node->type == AST_ASSIGN) {
            fprintf(out, "    %s = ", node->name);
            emit_expression(out, node->expr);
            fprintf(out, ";\n");

        } else if (node->type == AST_PRINT) {
            if (node->expr->type == EXPR_STRING) {
                fprintf(out, "    printf(\"%%s\\n\", ");
            } else {
                fprintf(out, "    printf(\"%%d\\n\", ");
            }
            emit_expression(out, node->expr);
            fprintf(out, ");\n");            

        } else if (node->type == AST_IF) {
            fprintf(out, "    if (");
            emit_expression(out, node->condition);
            fprintf(out, ") {\n");
            generate_code_internal(node->body, out, 1);
            fprintf(out, "    }");

            if (node->else_body) {
                fprintf(out, " else {\n");
                generate_code_internal(node->else_body, out, 1);
                fprintf(out, "    }\n");
            } else {
                fprintf(out, "\n");
            }

        } else if (node->type == AST_WHILE) {
            fprintf(out, "    while (");
            emit_expression(out, node->condition);
            fprintf(out, ") {\n");
            generate_code_internal(node->body, out, 1);
            fprintf(out, "    }\n");
        }
    }
}

static void emit_expression(FILE *out, Expr *expr) {
    switch (expr->type) {
        case EXPR_LITERAL:
            fprintf(out, "%d", expr->value);
            break;

        case EXPR_VARIABLE:
            fprintf(out, "%s", expr->name);
            break;
        
        case EXPR_STRING:
            fprintf(out, "\"%s\"", expr->name);
            break;
        

        case EXPR_BINARY: {
            int need_parens =
                expr->binary.op == '+' ||
                expr->binary.op == '-' ||
                expr->binary.op == '*' ||
                expr->binary.op == '/';

            if (need_parens) fprintf(out, "(");
            emit_expression(out, expr->binary.left);

            switch (expr->binary.op) {
                case '=': fprintf(out, " == "); break;
                case '!': fprintf(out, " != "); break;
                case 'l': fprintf(out, " <= "); break;
                case 'g': fprintf(out, " >= "); break;
                default:  fprintf(out, " %c ", expr->binary.op); break;
            }

            emit_expression(out, expr->binary.right);
            if (need_parens) fprintf(out, ")");
            break;
        }
    }
}

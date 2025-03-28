#include "compiler.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/ast.h"
#include "codegen/codegen.h"
#include "semantic/semantic.h"
#include <stdio.h>

int compile(const char *input_path, const char *output_path) {
    FILE *input = fopen(input_path, "r");
    if (!input) {
        perror("fopen input");
        return 1;
    }

    FILE *output = fopen(output_path, "w");
    if (!output) {
        perror("fopen output");
        fclose(input);
        return 1;
    }

    TokenList tokens = lex(input);
    ASTNode *ast = parse(&tokens);
    semantic_check(ast);
    generate_code(ast, output);    

    fclose(input);
    fclose(output);
    free_ast(ast);
    return 0;
}
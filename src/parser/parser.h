#ifndef PARSER_H
#define PARSER_H

#include "../lexer/lexer.h"
#include "ast.h"

ASTNode* parse(TokenList *tokens);

#endif
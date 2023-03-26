#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum SyntaxNodeType { BINOP, UNOP, PAREN, TOKEN, ERROR } SyntaxNodeType;

typedef struct SyntaxNode SyntaxNode;

struct SyntaxNode {
  SyntaxNodeType type;
  SyntaxNode *left;
  SyntaxNode *mid;
  SyntaxNode *right;
  Token *token;
};

typedef struct SyntaxTree SyntaxTree;

struct SyntaxTree {
  SyntaxNode *root;
};

Token **nextToken(Token **tokens);
SyntaxNode *newSyntaxNode(SyntaxNodeType type);
SyntaxNode *newTokenNode(Token **token);
SyntaxTree *parse(Token *tokens);
SyntaxNode *parse_expr(Token **tokens);
SyntaxNode *parse_term(Token **tokens);
SyntaxNode *parse_comma(Token **tokens);
SyntaxNode *parse_or(Token **tokens);
SyntaxNode *parse_and(Token **tokens);
SyntaxNode *parse_plus_minus(Token **tokens);
SyntaxNode *parse_mul(Token **tokens);
SyntaxNode *parse_primary(Token **tokens);
SyntaxNode *parse_func(Token **tokens);
SyntaxNode *parse_var(Token **tokens);
SyntaxNode *parse_paren(Token **tokens);
void free_syntax_node(SyntaxNode *node);
void free_syntax_tree(SyntaxTree *tree);
void print_syntax_node(SyntaxNode *node, int depth);
void print_syntax_tree(SyntaxTree *tree);

#endif

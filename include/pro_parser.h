#ifndef PRO_PARSER_H
#define PRO_PARSER_H

#include "lexer.h"

typedef enum SyntaxNodeType{
  BINOP,
  UNOP,
  PAREN,
  TOKEN
} SyntaxNodeType;


typedef struct SyntaxNode SyntaxNode;


struct SyntaxNode{
  SyntaxNodeType type;
  SyntaxNode* left;
  SyntaxNode* mid;
  SyntaxNode* right;
  Token* token;
};

typedef struct SyntaxTree SyntaxTree ;

struct SyntaxTree{
  SyntaxNode* root;
};


SyntaxTree* parse(Token* tokens);

void free_syntax_tree(SyntaxTree* tree);

#endif


#include "../include/pro_parser.h"
#include "../include/debug.h"
#include "../include/executor.h"
#include "../include/dictionary.h"
#include "../include/lexer.h"
#undef DEBUG
#define DEBUG 1

#define RAISE_ERROR                                                            \
  do {                                                                         \
    goto error;                                                                \
  } while (0)


typedef long (*op_t)(long, long);
op_t token_to_op(TokenType type) {
  switch (type) {
  case TOKEN_STAR:
    return mul;
  case TOKEN_PLUS:
    return add;
  case TOKEN_MINUS:
    return sub;
  case TOKEN_AND:
    return and;
  case TOKEN_OR:
    return or ;
  case TOKEN_XOR:
    return xor;
  case TOKEN_LS:
    return lshift;
  case TOKEN_RS:
    return rshift;
  case TOKEN_LR:
    return lrotate;
  case TOKEN_RR:
    return rrotate;
  case TOKEN_NOT:
    return not ;
  default:
    return NULL;
  }
}

long add(long a, long b) { return a + b; }
long sub(long a, long b) { return a - b; }
long mul(long a, long b) { return a * b; }
long and (long a, long b) { return a & b; }
long or (long a, long b) { return a | b; }
long xor (long a, long b) { return a ^ b; } long lshift(long a, long b) {
  return a << b;
}
long rshift(long a, long b) { return a >> b; }
long lrotate(long a, long b) {
  return (a << b) | (a >> (sizeof(long) * 8 - b));
}
long rrotate(long a, long b) {
  return (a >> b) | (a << (sizeof(long) * 8 - b));
}
long not(long a, long null) {
  // to resolve unused parameter warning
  null = 0;
  a = a + null;
  return ~a;
}
long paran(long a, long null) {
  // to resolve unused parameter warning
  null = 0;
  a = a + null;
  return a;
}

long str_to_long(char *str) {
  if (str == NULL) {
    return 0;
  }
  return atol(str);
}
bool error = false;

long eval_util(SyntaxNode *parent, Dictionary *dict) {
  if (error || parent == NULL || parent->type == ERROR)
    RAISE_ERROR;
  long left = 0;
  long right = 0;
  if (parent->type == BINOP || parent->type == UNOP || parent->type == PAREN)
    left = eval_util(parent->left, dict);
  if (parent->type == BINOP)
    right = eval_util(parent->right, dict);
  if (parent->type == TOKEN) {
    if (parent->token->type == TOKEN_LITERAL) {
      return parent->token->value;
    } else if (parent->token->type == TOKEN_IDENTIFIER) {
      size_t len = parent->token->length;
      char *var = (char*)malloc(sizeof(char) * (len + 1));
      strncpy(var, parent->token->start, len);
      var[len] = '\0';
      long val = get_var(dict, var);
      free(var);
      return val;
    }
  }
  if (parent->type == BINOP || parent->type == UNOP) {
    op_t op = token_to_op(parent->mid->token->type);
    if (op != NULL) {
      return op(left, right);
    }
  }
  if (parent->type == PAREN) {
    return left;
  }
  return 0;
error:
  error = true;
  return 0;
}
#define RAISE_EXEC_ERROR                                                           \
  do {                                                                         \
    goto execution_error;                                                                \
  } while (0)

char* exec(char *input, Dictionary *dict, bool *err) {
  error = false;

  char *output = NULL;
  size_t input_len = strlen(input);
  Lexer *lexer = lexer_new(input, input_len);
  SyntaxTree *tree = NULL;
  TokenType type = TOKEN_EOF;
  char *assign = NULL;
  do {
    lexer_next(lexer);
    type = lexer->token_list[lexer->cur_token - 1].type;
    if (type == TOKEN_UNKNOWN) {
      if(DEBUG)print_lex(lexer); 
      error = true;
      RAISE_EXEC_ERROR;
    }
    if (lexer->cur_token == 2 && type == TOKEN_EQ){
      if (lexer->token_list[0].type != TOKEN_IDENTIFIER) {
        error = true;
        RAISE_EXEC_ERROR;
      }
      size_t len = lexer->token_list[0].length;
      assign = (char*) malloc(sizeof(char) * (len + 1));
      strncpy(assign, lexer->token_list[0].start, len);
      assign[len] = '\0';
    }
  } while (type != TOKEN_EOF);
  if (assign)
     tree = parse(lexer->token_list + 2);
  else
    tree = parse(lexer->token_list );
  long res = eval_util(tree->root, dict);
  bool empty = false;
  if (tree->root == NULL && !assign) {
    error = false;
    empty = true;
  }
  if (error) 
    RAISE_EXEC_ERROR;
  else {
	print_lex(lexer);
    if (assign) {
      set_var(dict, assign, res);
    }
    else if (!empty){
      output = (char*)malloc(sizeof(char) * 20);
      snprintf(output, 20, "%ld", res);
      }

  }
execution_error:
  if(DEBUG && tree)print_syntax_tree(tree);
  if(tree)free_syntax_tree(tree);
  if(lexer)lexer_free(lexer);
  if(assign)free(assign);
  *err = error;
  return output;
}



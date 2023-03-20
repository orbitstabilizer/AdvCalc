#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LEN 257

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum TokenType {

  TOKEN_UNKNOWN,    // 0
  TOKEN_LITERAL,    // 1
  TOKEN_IDENTIFIER, // 2

  TOKEN_STAR,  // 3
  TOKEN_PLUS,  // 4
  TOKEN_MINUS, // 5

  TOKEN_AND, // 6
  TOKEN_OR,  // 7
  TOKEN_NOT, // 8
  TOKEN_XOR, // 9

  TOKEN_LS, // 10
  TOKEN_RS, // 11
  TOKEN_LR, // 12
  TOKEN_RR, // 13

  TOKEN_EQ,      // 14
  TOKEN_COMMENT, // 15
  TOKEN_EOF,     // 16

  TOKEN_LEFT_PAREN,  // 17
  TOKEN_RIGHT_PAREN, // 18
  TOKEN_COMMA,       // 19
} TokenType;

typedef struct Token Token;
struct Token {
  TokenType type;
  char *start;
  size_t length;
  long value;
};

typedef struct Lexer Lexer;
struct Lexer {
  char *input;
  size_t cur_pos;
  size_t input_len;

  Token token_list[MAX_TOKEN_LEN];
  size_t cur_token;
};

Lexer *lexer_new(char *input, size_t input_len);
void lexer_free(Lexer *lexer);
void print_lex(Lexer *lexer);
void lexer_next(Lexer *lexer);
bool parseLong(const char *str, long *val);

#endif

#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LEN 257

#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef enum TokenType{
    
    TOKEN_UNKNOWN, 
    TOKEN_LITERAL,
    TOKEN_IDENTIFIER,

    TOKEN_STAR,
    TOKEN_PLUS,
    TOKEN_MINUS,

    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_XOR,

    TOKEN_LS,
    TOKEN_RS,
    TOKEN_LR,
    TOKEN_RR,
    
    TOKEN_WHITE_SPACE,
    TOKEN_EQ,
    TOKEN_COMMENT,
    TOKEN_EOF,
    
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_COMMA,
} TokenType;


typedef struct Token Token;
struct Token{
  TokenType type;
  char *start;
  size_t length;
  long value;
};

typedef struct Lexer Lexer; 
struct Lexer{
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
Token* next_token(char *source, size_t length);

#endif

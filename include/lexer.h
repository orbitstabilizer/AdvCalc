#ifndef LEXER_H
#define LEXER_H


#include <ctype.h>
typedef enum TokenType{
    
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
    
    TOKEN_UNKNOWN,
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


Token* next_token(char *source, size_t length);

#endif

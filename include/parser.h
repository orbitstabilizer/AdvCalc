#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


typedef struct Expr Expr; 
size_t find(char* input, size_t size, char c);
size_t strip(char* input, size_t size);
bool is_inside_phrentesis(char* input, size_t size);
Expr* parse_expr(char* input, size_t size); 
int parse_op(char* c, size_t size); 
Expr* parse_func(char* input, size_t size);
Expr* extract_expression(char* input, size_t size);
bool is_l_value(char* input, size_t size);
bool is_r_value(char* input, size_t size);

static const char* ops[] = {
    "+",
    "-",
    "*",
    "&",
    "|",
    "xor",
    "ls",
    "rs",
    "lr",
    "rr",
    "not",
};

static const size_t N_OPS = sizeof(ops) / sizeof(ops[0]);

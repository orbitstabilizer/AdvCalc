#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct Expr Expr; 
size_t find(char* input, size_t size, char c);
size_t strip(char* input, size_t size);
bool is_inside_phrentesis(char* input, size_t size);
Expr* parse_expr(char* input, size_t size); 
int parse_op(char* c, size_t size); // TODO: operator and variable names can be the same
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


struct Expr{
    Expr* expr_l;
    Expr* expr_r;
    char* op;
    char* value;
    int value_length;

};

size_t find(char* input, size_t size, char c){
    for (size_t i = 0; i < size; i++){
        if(input[i] == c)
            return i;
    }
    return -1;
}

size_t strip(char* input, size_t size){
    size_t i = 0;
    while (i < size && input[i] == ' '){
        i++;
    }
    size_t j = size - 1;
    while (j > i && input[j] == ' '){
        j--;
    }
    for (size_t k = 0; k < j - i + 1; k++){
        input[k] = input[k + i];
    }
    return j - i + 1;
}

bool is_inside_phrentesis(char* input, size_t size){
    if(size == 0)
        return false;
    if(input[0] != '(' || input[size - 1] != ')')
        return false;
    
    int pharentesis_level = 0;
    for (size_t i = 0; i < size - 1; i++){
        if (input[i] == '('){
            pharentesis_level++;
        } else if (input[i] == ')'){
            pharentesis_level--;
        }
        if(pharentesis_level < 1)
            return false;
    }
    return true;
}

int parse_op(char* c, size_t size){
    for (size_t i = 0; i < N_OPS; i++){
        if(size == strlen(ops[i])){
            bool match = true;
            for (size_t j = 0; j < size; j++){
                if(c[j] != ops[i][j]){
                    match = false;
                    break;
                }
            }
            if(match)
                return i;
        }
    }
    return -1;
}

Expr* parse_expr(char* input, size_t size){

    size = strip(input, size);

    if(is_inside_phrentesis(input, size)){
        return parse_expr(input + 1, size - 2);
    }


    
    Expr* expr = parse_func(input, size);
    if(expr != NULL) return expr;
    
    expr = (Expr*) malloc(sizeof(Expr));
    expr->expr_l = NULL;
    expr->expr_r = NULL;
    expr->op = NULL;
    expr->value = NULL;
    
    size_t operator_index = -1; // TODO: operator precedence
    int pharentesis_level = 0;

    for (size_t i = 0; i < size; i++){
        if (input[i] == '('){
            pharentesis_level++;
        } else if (input[i] == ')'){
            pharentesis_level--;
        } else{
            if(pharentesis_level == 0){
                if(parse_op(input, 1) != -1){
                    operator_index = i;
                    break;
                }
            }
        }
    }

    if (operator_index == -1){
        expr->op = extract_expression(input, size);
        return expr;
    }
    
    expr->op = input[operator_index];
    expr->expr_l = parse_expr(input, operator_index);
    expr->expr_r = parse_expr(input + operator_index + 1, size - operator_index - 1);


    return expr;
}

Expr* parse_func(char* input, size_t size){

    

    if(size <= 2 || parse_op(input, 2) == -1){
        return NULL;
    }
    if(size == 3 || parse_op(input, 3) == -1){
        return NULL;
    }

    size_t i = find(input, size, '(');
    
    if(i == -1)
        return NULL;

    Expr* expr = (Expr*) malloc(sizeof(Expr));
    expr->expr_l = NULL;
    expr->expr_r = NULL;
    expr->op = input;
    expr->value = NULL;
    
    expr->expr_l = parse_expr(input + i + 1, size - i - 2);

    i = find(input, size, ',');

    if(i != -1)
        expr->expr_r = parse_expr(input + i + 1, size - i - 2);

    return expr;
}

Expr* extract_expression(char* input, size_t size){
    if(is_r_value(input, size)){
        Expr* expr = (Expr*) malloc(sizeof(Expr));
        expr->expr_l = NULL;
        expr->expr_r = NULL;
        expr->op = NULL;
        expr->value = input;
        expr->value_length = size;
        return expr;
    }
    // TODO: error handling
    return NULL;
}

bool is_l_value(char* input, size_t size){
    for(size_t i = 0; i < size; i++){
        if(!isalpha(input[i]))
            return false;
    }
    return true;
}

bool is_r_value(char* input, size_t size){
    if(is_l_value(input, size))
        return true;

    for(size_t i = 0; i < size; i++){
        if(!isdigit(input[i]))
            return false;
    }
    return true;
}
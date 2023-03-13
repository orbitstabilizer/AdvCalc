typedef struct Expr Expr; 
Expr* parse(char* input); 
bool is_inside_phrentesis(char* input, size_t size);
int parse_op(char* c); // TODO: operator and variable names can be the same
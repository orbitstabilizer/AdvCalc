#include <string.h>
#include "../include/pro_parser.h"
#include "../include/debug.h"

Token** nextToken(Token** tokens);
SyntaxNode* newSyntaxNode(SyntaxNodeType type);
SyntaxNode* newTokenNode(Token** token);
SyntaxTree* parse(Token* tokens);
SyntaxNode* parse_expr(Token** tokens);
SyntaxNode* parse_term(Token** tokens);
SyntaxNode* parse_comma(Token** tokens);
SyntaxNode* parse_or(Token** tokens);
SyntaxNode* parse_and(Token** tokens);
SyntaxNode* parse_plus_minus(Token** tokens);
SyntaxNode* parse_mul(Token** tokens);
SyntaxNode* parse_primary(Token** tokens);
SyntaxNode* parse_func(Token** tokens);
SyntaxNode* parse_var(Token** tokens);
SyntaxNode* parse_paren(Token** tokens);
void free_syntax_node(SyntaxNode* node);
void free_syntax_tree(SyntaxTree* tree);
void printSyntaxNode(SyntaxNode* node, int depth);
void printSyntaxTree(SyntaxTree* tree);

Token** nextToken(Token** tokens){
    ++(*tokens);
    return tokens;
}

SyntaxNode* newSyntaxNode(SyntaxNodeType type){
    SyntaxNode* node = (SyntaxNode*)malloc(sizeof(SyntaxNode));
    node->type = type;
    node->left = NULL;
    node->mid = NULL;
    node->right = NULL;
    node->token = NULL;
    return node;
}


SyntaxNode* newTokenNode(Token** token){
    SyntaxNode* node = (SyntaxNode*)newSyntaxNode(TOKEN);
    node->token = *token;
    return node;
}

SyntaxTree* parse(Token* tokens){
    
    fprintf(stderr, "parsing...\n");

    SyntaxTree* tree = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    tree->root = (SyntaxNode*)parse_expr(&tokens);
    return tree;
}

SyntaxNode* parse_expr(Token** tokens){
    if((*tokens)->type == TOKEN_EOF) return NULL;
    SyntaxNode* node = parse_term(tokens);
    if((*tokens)->type != TOKEN_EOF) {
        node->type = ERROR;
        fprintf(stderr, "Error: Expected EOF, got %s\n", (*tokens)->start);
    }
    return node;
}

SyntaxNode* parse_term(Token** tokens){
    return parse_comma(tokens);
}

SyntaxNode* parse_comma(Token** tokens){
    
    SyntaxNode* left = parse_or(tokens);
    
    while((*tokens)->type == TOKEN_COMMA){
        
        SyntaxNode* node = (SyntaxNode*)newSyntaxNode(BINOP);
        
        node->left = left;
        node->mid = (SyntaxNode*)newTokenNode(tokens);
        node->right = (SyntaxNode*)parse_or(nextToken(tokens));
        
        left = node;
    }
    return left;
}

SyntaxNode* parse_or(Token** tokens){
    
    SyntaxNode* left = parse_and(tokens);
    
    while((*tokens)->type == TOKEN_OR){
        
        SyntaxNode* node = (SyntaxNode*)newSyntaxNode(BINOP);
        
        node->left = left;
        node->mid = (SyntaxNode*)newTokenNode(tokens);
        node->right = (SyntaxNode*)parse_and(nextToken(tokens));
        
        left = node;
    }
    return left;
}
SyntaxNode* parse_and(Token** tokens){
        
        SyntaxNode* left = parse_plus_minus(tokens);
        
        while((*tokens)->type == TOKEN_AND){
            
            SyntaxNode* node = (SyntaxNode*)newSyntaxNode(BINOP);
            
            node->left = left;
            node->mid = (SyntaxNode*)newTokenNode(tokens);
            node->right = (SyntaxNode*)parse_plus_minus(nextToken(tokens));
            
            left = node;
        }
        return left;
}

SyntaxNode* parse_plus_minus(Token** tokens){
    
    SyntaxNode* left = parse_mul(tokens);
    
    while((*tokens)->type == TOKEN_PLUS || (*tokens)->type == TOKEN_MINUS){
        
        SyntaxNode* node = (SyntaxNode*)newSyntaxNode(BINOP);
        
        node->left = left;
        node->mid = (SyntaxNode*)newTokenNode(tokens);
        node->right = (SyntaxNode*)parse_mul(nextToken(tokens));
        
        left = node;
    }
    return left;
}

SyntaxNode* parse_mul(Token** tokens){
    
    SyntaxNode* left = parse_primary(tokens);
    
    while((*tokens)->type == TOKEN_STAR){
        
        SyntaxNode* node = newSyntaxNode(BINOP);
        
        node->left = (SyntaxNode*)left;
        node->mid = (SyntaxNode*)newTokenNode(tokens);
        node->right = (SyntaxNode*)parse_primary(nextToken(tokens));

        left = node;
    }
    return left;
}

SyntaxNode* parse_primary(Token** tokens){
    return parse_func(tokens);
}

SyntaxNode* parse_func(Token** tokens){
    if((*tokens)->type == TOKEN_XOR || 
        (*tokens)->type == TOKEN_LS || (*tokens)->type == TOKEN_RS || 
        (*tokens)->type == TOKEN_LR || (*tokens)->type == TOKEN_RR)
    {
        SyntaxNode* node = newSyntaxNode(BINOP);
        node->mid = newTokenNode(tokens);
        
        SyntaxNode* temp = parse_paren(nextToken(tokens));

        if(temp != NULL && temp->left != NULL && temp->left->mid != NULL && temp->left->mid->token->type == TOKEN_COMMA){
            node->left = temp->left->left;
            node->right = temp->left->right;
        }
        else{
            node->type = ERROR;
            free_syntax_node(temp);
            TODO("error message: invalid function call");
        }
        return node;
    }
    else if((*tokens)->type == TOKEN_NOT){
        SyntaxNode* node = newSyntaxNode(UNOP);
        node->mid = newTokenNode(tokens);
        
        SyntaxNode* temp = parse_paren(nextToken(tokens));
        if(temp != NULL && temp->left != NULL && (temp->left->mid == NULL || temp->left->mid->token->type != TOKEN_COMMA)){
            node->left = temp->left;
        }
        else{
            node->type = ERROR;
            free(temp);
            TODO("error message: invalid function call");
        }
        return node;
    }
    return parse_var(tokens);
}

SyntaxNode* parse_var(Token** tokens){
    if((*tokens)->type == TOKEN_IDENTIFIER || (*tokens)->type == TOKEN_LITERAL){
        SyntaxNode* node = newTokenNode(tokens);
        nextToken(tokens);
        return node;
    }
    return parse_paren(tokens);
}

SyntaxNode* parse_paren(Token** tokens){
    
    if((*tokens)->type == TOKEN_LEFT_PAREN){
        SyntaxNode* node = newSyntaxNode(PAREN);
        node->left = parse_term(nextToken(tokens));
        
        if((*tokens)->type == TOKEN_RIGHT_PAREN){
            nextToken(tokens);
        }
        else{
            node->type = ERROR;
            TODO("closing parenthesis error message");
            fprintf(stderr, "Expected closing parenthesis\n");
        }

        return node;
    }
    return NULL;
}

void free_syntax_node(SyntaxNode* node){
    if(node == NULL) return;
    free_syntax_node(node->left);
    free_syntax_node(node->mid);
    free_syntax_node(node->right);
    free(node);
}

void free_syntax_tree(SyntaxTree* tree){
    if(tree == NULL) return;
    free_syntax_node(tree->root);
    free(tree);
}

void printSyntaxNode(SyntaxNode* node, int depth){
    if(node == NULL) return;
    for(int i = 0; i < depth; ++i){
        fprintf(stderr, "-  ");
    }
    switch(node->type){
        case TOKEN:
            fprintf(stderr, "|__ TOKEN(\"");
            for(size_t i = 0; i < node->token->length; ++i)
                fprintf(stderr, "%c", node->token->start[i]);
            fprintf(stderr, "\")\n");
            break;
        case BINOP:
            fprintf(stderr, "|__ OPERATOR(%c)\n", node->mid->token->start[0]);
            break;
        case PAREN:
            fprintf(stderr, "|__ PARENTHESIS\n");
            break;
        case UNOP:
            fprintf(stderr, "|__ UNARY(NOT)\n");
            break;
        case ERROR:
            fprintf(stderr, "ERROR\n");
            break;
        default:
            fprintf(stderr, "UNKNOWN\n");
            break;
    };
    printSyntaxNode(node->left, depth + 1);
    printSyntaxNode(node->right, depth + 1);
};

void printSyntaxTree(SyntaxTree* tree){
    fprintf(stderr, "printing syntax tree...\n");
    printSyntaxNode(tree->root, 0);
}

void test_pro_parser(char* input){
    size_t input_len = strlen(input);
    Lexer *lexer = lexer_new(input, input_len);
    do {
        lexer_next(lexer);
    } while (lexer->token_list[lexer->cur_token -1].type != TOKEN_EOF);

    print_lex(lexer);

    SyntaxTree* tree = (SyntaxTree*)parse(lexer->token_list);
    printSyntaxTree(tree);

    lexer_free(lexer);
    free_syntax_tree(tree);
}

/*
int main(){
    char *input = "(xor((xor ()(a,b)),b))";
    test_pro_parser(input);
}
*/
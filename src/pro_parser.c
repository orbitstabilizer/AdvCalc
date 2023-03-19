#include <string.h>
#include "../include/pro_parser.h"
#include "../include/debug.h"

Token** nextToken(Token** tokens);
SyntaxNode* newSyntaxNode(SyntaxNodeType type);
SyntaxNode* newTokenNode(Token** token);
SyntaxTree* parse(Token* tokens);
SyntaxNode* parse_expr(Token** tokens);
SyntaxNode* parse_term(Token** tokens);
SyntaxNode* parse_plus_minus(Token** tokens);
SyntaxNode* parse_mul(Token** tokens);
SyntaxNode* parse_primary(Token** tokens);
SyntaxNode* parse_paren(Token** tokens);
SyntaxNode* parse_var(Token** tokens);
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
    return parse_term(tokens);
}

SyntaxNode* parse_term(Token** tokens){
    
    return parse_plus_minus(tokens);
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
    SyntaxNode* node = parse_paren(tokens);
    if(node == NULL) return parse_var(tokens);
    else return node;
}

SyntaxNode* parse_paren(Token** tokens){
    if((*tokens)->type == TOKEN_LEFT_PAREN){

        SyntaxNode* node = newSyntaxNode(PAREN);
        node->left = parse_expr(nextToken(tokens));
        
        if((*tokens)->type == TOKEN_RIGHT_PAREN){
            nextToken(tokens);
        }
        else{
            node->type = ERROR;
            TODO("closing parenthesis error message");
            // error("Expected closing parenthesis"); 
        }

        return node;
    }
    return NULL;
}

SyntaxNode* parse_var(Token** tokens){
    if((*tokens)->type == TOKEN_IDENTIFIER || (*tokens)->type == TOKEN_LITERAL){
        SyntaxNode* node = newTokenNode(tokens);
        nextToken(tokens);
        return node;
    }
    else{
        return NULL;
    }
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
            printSyntaxNode(node->left, depth + 1);
            printSyntaxNode(node->right, depth + 1);
            break;
        case PAREN:
            fprintf(stderr, "|__ PARENTHESIS\n");
            printSyntaxNode(node->left, depth + 1);
            break;
        case ERROR:
            fprintf(stderr, "ERROR\n");
            break;
        default:
            fprintf(stderr, "UNKNOWN\n");
            break;
    };
};

void printSyntaxTree(SyntaxTree* tree){
    fprintf(stderr, "printing syntax tree...\n");
    printSyntaxNode(tree->root, 0);
}

void test(char* input){
    size_t input_len = strlen(input);
    Lexer *lexer = lexer_new(input, input_len);
    do {
        lexer_next(lexer);
    } while (lexer->token_list[lexer->cur_token -1].type != TOKEN_EOF);

    print_lex(lexer);

    SyntaxTree* tree = (SyntaxTree*)parse(lexer->token_list);
    printSyntaxTree(tree);

    lexer_free(lexer);
}

int main(){
    char *input = "(a+b)*2*4+5*(a*a)";
    test(input);
}
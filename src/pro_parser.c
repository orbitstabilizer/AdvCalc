#include "../include/pro_parser.h"
#include "../include/debug.h"

Token* next(Token* tokens){
    return (Token*)++tokens;
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

SyntaxTree* parse(Token* tokens){
    SyntaxTree* tree = (SyntaxTree*)malloc(sizeof(SyntaxTree));
    tree->root = (SyntaxNode*)parse_expr(&tokens);
    return tree;
}

SyntaxNode* parse_expr(Token** tokens){
    if((*tokens)->type == TOKEN_EOF) return NULL;
    return parse_paren(tokens);
}


SyntaxNode* parse_paren(Token** tokens){
    if((*tokens)->type == TOKEN_LEFT_PAREN){
        ++*tokens;

        SyntaxNode* node = newSyntaxNode(PAREN);
        node->left = parse_expr(tokens);
        
        if((*tokens)->type == TOKEN_RIGHT_PAREN){
            ++*tokens;
        }
        else{
            node->type = ERROR;
            TODO("closing parenthesis error message");
            error("Expected closing parenthesis"); 
        }

        return node;
    }
    else{
        return parse_func(tokens);
    }
}

SyntaxNode* parse_func(Token** tokens){
    if((*tokens)->type == TOKEN_XOR || (*tokens)->type == TOKEN_LR || (*tokens)->type == TOKEN_RR || (*tokens)->type == TOKEN_LS || (*tokens)->type == TOKEN_RS){
        UNIMPLEMENTED("parse_func");
    }
    else if((*tokens)->type == TOKEN_NOT){
        UNIMPLEMENTED("parse_func");
    }
    else{
        return parse_var(tokens);
    }
}

SyntaxNode* parse_var(Token** tokens){
    if((*tokens)->type == TOKEN_IDENTIFIER || (*tokens)->type == TOKEN_LITERAL){
        SyntaxNode* node = (SyntaxNode*)newTokenNode(tokens);
        return parse_mul(++*tokens, node);
    }
    else{
        TODO("unexpected token error message");
        error("unexpected token"); 
        return NULL;
    }
}

SyntaxNode* parse_mul(Token** tokens, SyntaxNode* left){
    while((*tokens)->type == TOKEN_STAR){
        SyntaxNode* node = newSyntaxNode(BINOP);
        node->left = (SyntaxNode*)left;
        node->mid = (SyntaxNode*)newTokenNode(tokens);
        node->right = (SyntaxNode*)parse_expr(++*tokens);
    }
    return parse_plus_minus(tokens, left);
}

SyntaxNode* parse_plus_minus(Token** tokens, SyntaxNode* left){
    while((*tokens)->type == TOKEN_PLUS || (*tokens)->type == TOKEN_MINUS){
        SyntaxNode* node = (SyntaxNode*)newSyntaxNode(BINOP);
        node->left = (SyntaxNode*)left;
        node->mid = (SyntaxNode*)newTokenNode(tokens);
        node->right = (SyntaxNode*)parse_expr(++*tokens);
    }
    return parse_unary(tokens, left);
}

// SyntaxNode* parse_and(Token** tokens, SyntaxNode* left){
//     while((*tokens)->type == TOKEN_AND){
//         SyntaxNode* node = newSyntaxNode(BINOP);
//         node->left = left;
//         node->mid = newTokenNode(tokens);
//         node->right = parse_expr(++*tokens);
//     }
//     return parse_or(tokens, left);
// }


// SyntaxNode* parse_or(Token** tokens, SyntaxNode* left){
//     while((*tokens)->type == TOKEN_OR){
//         SyntaxNode* node = newSyntaxNode(BINOP);
//         node->left = left;
//         node->mid = newTokenNode(tokens);
//         node->right = parse_expr(++*tokens);
//     }
//     return parse_unary(tokens, left);
// }

SyntaxNode* parse_unary(Token** tokens, SyntaxNode* left){
    ++*tokens;
    return left;
}

SyntaxNode* newTokenNode(Token** token){
    SyntaxNode* node = (SyntaxNode*)newSyntaxNode(TOKEN);
    node->token = *token;
    return node;
}
#include "../include/lexer.h"
#include "../include/debug.h"



Lexer *lexer_new(char *input, size_t input_len){
    Lexer *lexer =  malloc(sizeof(Lexer));
    lexer->input = input;
    lexer->cur_pos = 0;
    lexer->input_len = input_len;
    lexer->cur_token = 0;
    return lexer;

}

void lexer_free(Lexer *lexer){
    free(lexer);
}

void print_lex(Lexer *lexer){
    printf("Lexer{\n\tinput: `%s`\n\tcur_pos: %zu\n\tinput_len: %zu\n\tcur_token: %zu\n",
           lexer->input, lexer->cur_pos, lexer->input_len, lexer->cur_token);
    printf("\tToken List:{\n");
    for (size_t i = 0; i < lexer->cur_token; i++){
        Token *token = &lexer->token_list[i];
        char sub_str[token->length + 1];
        strncpy(sub_str, token->start, token->length);
        sub_str[token->length] = '\0';

        printf("\t\tToken{\n\t\t\ttype: %d\n\t\t\tvalue: %ld\n\t\t\tlength: %zu\n\t\t\tstart: '%s'\n\t\t},\n",
               token->type, token->value, token->length, sub_str);
    }
    printf("\t}\n");
    printf("}\n");
}

void init_token(Token *token, TokenType type, long value, size_t value_len, char* start ){
    token->type = type;
    token->value = value;
    token->length = value_len;
    token->start = start;
    if (type == TOKEN_LITERAL){
        char sub_str[value_len + 1];
        strncpy(sub_str, start, value_len);
        sub_str[value_len] = '\0';
        TODO("Check if it is a valid number");
        token->value = strtol(sub_str, NULL, 10);
    }
}


void lexer_next(Lexer *lexer){
    Token* token = &lexer->token_list[lexer->cur_token];
    if (lexer->cur_pos >= lexer->input_len){
        init_token(token, TOKEN_EOF, 0, 0,  NULL);
        lexer->cur_token++;
        return;
    }
    char c = lexer->input[lexer->cur_pos];
    if (c == ' ' || c == '\t' || c == '\n'){
        while (c == ' ' || c == '\t' || c == '\n'){
            lexer->cur_pos++;
            c = lexer->input[lexer->cur_pos];
        }
    }
    switch (c){
        case '+':
            init_token(token, TOKEN_PLUS, 0, 1, &lexer->input[lexer->cur_pos]);
            break;
        case '-':
            init_token(token, TOKEN_MINUS, 0, 1, &lexer->input[lexer->cur_pos]);
            break;
        case '*':
            init_token(token, TOKEN_STAR, 0, 1, &lexer->input[lexer->cur_pos]);
            break;
        case '(':
            init_token(token, TOKEN_LEFT_PAREN, 0, 1, &lexer->input[lexer->cur_pos]);
            break;
        case ')':
            init_token(token, TOKEN_RIGHT_PAREN, 0, 1, &lexer->input[lexer->cur_pos]);
            break;
        case '=':
            init_token(token, TOKEN_EQ, 0, 1, &lexer->input[lexer->cur_pos]);
            break;
    }
    if (isalpha(c)){
        int start = lexer->cur_pos;
        while (isalpha(c)){
            lexer->cur_pos++;
            c = lexer->input[lexer->cur_pos];
        }
        init_token(token, TOKEN_IDENTIFIER, 0, lexer->cur_pos - start, &lexer->input[start]);
        lexer->cur_token++;
        return;
    }else if (isdigit(c)){
        int start = lexer->cur_pos;
        while (isdigit(c)){
            lexer->cur_pos++;
            c = lexer->input[lexer->cur_pos];
        }
        init_token(token, TOKEN_LITERAL, 0, lexer->cur_pos - start, &lexer->input[start]);
        lexer->cur_token++;
        return;
    }
    else{
        lexer->cur_pos++;
        lexer->cur_token++;
    }

    return;
}
/*
int main(){
    char *input = "abc = (a + b) - cenk*31 + 696789876789876789876787";
    size_t input_len = strlen(input);
    Lexer *lexer = lexer_new(input, input_len);
    do {
        lexer_next(lexer);
   } while (lexer->token_list[lexer->cur_token -1].type != TOKEN_EOF);
   
    print_lex(lexer);

    lexer_free(lexer);

}
*/



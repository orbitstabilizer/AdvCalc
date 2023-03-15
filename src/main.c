#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> 
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/debug.h"


#define BUFFER_SIZE 256


int main() {
  // plus 1 for null terminator 
  char buffer[BUFFER_SIZE+1];
  while (true) {
    printf("> ");
    TODO("Fix buffer overflow, when input is too long it carrys over to the next line");
    if(fgets(buffer, BUFFER_SIZE+1, stdin) == NULL)
      break;
    printf("You entered: %s\n", buffer); 
    
    // returns a pointer to the first token
    size_t buffer_len = strlen(buffer); 
    TODO("operator and variable names can be the same");
    Expr* parse_tree = parse_expr(buffer, buffer_len);
      
    char* output = eval(parse_tree);
    size_t len = strlen(output); 
    if(output){
      printf("%s\n", output);
      printf("len: %zu\n", len);
    }
  }
  return 0;

}

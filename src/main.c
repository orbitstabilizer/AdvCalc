#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> 
#include "../include/parser.h"
#include "../include/executor.h"


#define BUFFER_SIZE 256


int main() {
  char buffer[BUFFER_SIZE];
  while (true) {
    printf("> ");
    // TODO: Fix buffer overflow
    if(fgets(buffer, BUFFER_SIZE+1, stdin) == NULL)
      break;
    printf("You entered: %s\n", buffer); 
    
    // returns a pointer to the first token
    Token* parse_tree = parse(buffer);
      
    char* output = eval(parse_tree);
    size_t len = strlen(output); 
    if(output){
      printf("%s\n", output);
    }
  }
  return 0;

}

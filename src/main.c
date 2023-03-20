#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> 
#include "../include/executor.h"
#include "../include/debug.h"


#define BUFFER_SIZE 256


int main() {
  // plus 1 for null terminator 
  char buffer[BUFFER_SIZE+1];
  Dictionary *dict = new_dictionary();
  while (true) {
    printf("> ");
    TODO("Fix buffer overflow, when input is too long it carrys over to the next line");
    if(fgets(buffer, BUFFER_SIZE+1, stdin) == NULL)
      break;
    bool error = false;
    char* output = exec(buffer, dict, &error);

    if(output){
      printf("%s\n", output);
    }
    else if(error)
      printf("Error!\n");
    free(output);
  }
  if(dict)free_dict(dict);
  return 0;

}

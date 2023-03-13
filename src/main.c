#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define BUFFER_SIZE 256


int main() {
  char buffer[BUFFER_SIZE];
  while (true) {
    printf("> ");
    if(fgets(buffer, BUFFER_SIZE, stdin) == NULL)
      break;
    printf("You entered: %s\n", buffer); 
  }
  return 0;

}

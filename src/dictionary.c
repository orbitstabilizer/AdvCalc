#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"
#define UNIMPLEMENTED do{ printf("ERROR: not implemented at line : %d", __LINE__); exit(1); }while(0)


void declare_var(char *name){
  setenv(name, "0", 1); 
}

void set_var(char *name, int value){
  // int to string
  char value_str[10];
  sprintf(value_str, "%d", value);
  setenv(name, value_str, 1);
}

long get_var(char *name){
  char* value_str = getenv(name);
  if(value_str == NULL){
    // if varialbe is not declared 
    return 0;
  }
  return atol(value_str);
}


int main(){
  declare_var("a");
  set_var("a", 31);
  printf("Value of a is %ld\n", get_var("a"));
  return 0;
}


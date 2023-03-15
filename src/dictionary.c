#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dictionary.h"


void declare_var(char *name){
  setenv(name, "0", 1); 
}

void set_var(char *name, long value){
  // int to string
  char value_str[10];
  sprintf(value_str, "%ld", value);
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

/*
int main(){
  declare_var("a");
  set_var("a", 31);
  printf("Value of a is %ld\n", get_var("a"));
  return 0;
}
*/

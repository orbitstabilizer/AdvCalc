#include <stdio.h>
#include <stdlib.h>


int main(){
  const char* var_name = "a";
  const char* value = "1";

  // setenv(var_name, value, 1);

  printf("Value of %s is %s\n", var_name, getenv("b"));
  return 0;
}

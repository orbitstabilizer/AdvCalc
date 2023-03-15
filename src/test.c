#include <stdio.h>
#include "../include/dictionary.h"


int main(){
  declare_var("a");
  declare_var("b");
  set_var("a", 5);
  set_var("b", 10);
  long sum = get_var("a") + get_var("b");
  printf("Value of a is %ld\n", get_var("a"));
  printf("Value of b is %ld\n", get_var("b"));
  printf("Sum of a and b is %ld\n", sum);

  return 0;
}

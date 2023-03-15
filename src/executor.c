#include "../include/executor.h"
#include "../include/debug.h"

long str_to_long(char* str);

long add(long a, long b);
long sub(long a, long b);
long mul(long a, long b);
long and(long a, long b);
long or(long a, long b);
long xor(long a, long b);
long lshift(long a, long b);
long rshift(long a, long b);
long lrotate(long a, long b);
long rrotate(long a, long b);
long not(long a, long null);

long (*binop[])(long, long) = {
  add, sub, mul, and, or, xor, lshift, rshift, lrotate, rrotate
};

long add(long a, long b){
  return a + b;
}
long sub(long a, long b){
  return a - b;
}
long mul(long a, long b){
  return a * b;
}
long and(long a, long b){
  return a & b;
}
long or(long a, long b){
  return a | b;
}
long xor(long a, long b){
  return a ^ b;
}
long lshift(long a, long b){
  return a << b;
}
long rshift(long a, long b){
  return a >> b;
}
long lrotate(long a, long b){
  return (a << b) | (a >> (sizeof(long) * 8 - b));
}
long rrotate(long a, long b){
  return (a >> b) | (a << (sizeof(long) * 8 - b));
}
long not(long a, long null){
  // to resolve unused parameter warning
  null = 0;
  a = a+null;
  return ~a;
}

long str_to_long(char* str){
  if (str == NULL){
    return 0;
  }
  return atol(str);
}


char* eval(Expr* parse_tree){ 
  UNIMPLEMENTED("eval");
  return parse_tree->value;
}


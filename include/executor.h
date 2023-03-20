#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../include/pro_parser.h"
#include "../include/dictionary.h"

int exec(Dictionary *dict, char *input, char *output);
long str_to_long(char *str);
long add(long a, long b);
long sub(long a, long b);
long mul(long a, long b);
long b_and (long a, long b);
long b_or (long a, long b);
long b_xor (long a, long b);
long lshift(long a, long b);
long rshift(long a, long b);
long lrotate(long a, long b);
long rrotate(long a, long b);
long b_not(long a, long null);

#endif

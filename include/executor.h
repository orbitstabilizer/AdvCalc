#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../include/pro_parser.h"
#include "../include/dictionary.h"

char *exec(char *input, Dictionary *dict, bool *error);
long str_to_long(char *str);
long add(long a, long b);
long sub(long a, long b);
long mul(long a, long b);
long and (long a, long b);
long or (long a, long b);
long xor (long a, long b);
long lshift(long a, long b);
long rshift(long a, long b);
long lrotate(long a, long b);
long rrotate(long a, long b);
long not(long a, long null);

#endif

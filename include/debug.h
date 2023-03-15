#ifndef DEBUG_H
#define DEBUG_H

#include <stdlib.h>
#include <stdio.h>
#define UNIMPLEMENTED(func_name) do{ printf("ERROR: '%s' is not implemented in file: %s line: %d \n", func_name, __FILE__, __LINE__); exit(1); }while(0)
#define TODO(action) do{ printf("TODO:  '%s' in file: %s line: %d \n", action, __FILE__, __LINE__); }while(0)


#endif

INCLUDE_DIR=./include/
EXEC=advcalc
CC=gcc
CFLAGS=-I $(INCLUDE_DIR) -o $(EXEC) -Wall -Wextra -Werror -pedantic #-fsanitize=address -g

SRC=$(filter-out ./src/test.c, $(wildcard ./src/*.c))

default: clean advcalc

clean :
	if [ -f $(EXEC) ] ; then rm $(EXEC) ; fi
	
advcalc:  
	$(CC) $(SRC) $(CFLAGS)



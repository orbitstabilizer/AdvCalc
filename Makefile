INCLUDE_DIR=./include/
EXEC=advcalc
CC=gcc
CFLAGS=-I $(INCLUDE_DIR) -o $(EXEC) -Wall -Wextra -Werror -pedantic 

SRC=$(filter-out ./src/test.c, $(wildcard ./src/*.c))

clean :
	rm $(EXEC)

advcalc:  
	$(CC) $(SRC) $(CFLAGS)



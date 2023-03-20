INCLUDE_DIR=./include/
EXEC=advcalc
CC=gcc
DEBUG_CFLAGS=-I $(INCLUDE_DIR) -o $(EXEC) --std=gnu11  -Wall -Wextra  -pedantic -fsanitize=address -g 
BUILD_CFLAGS=-I $(INCLUDE_DIR) -o $(EXEC) --std=gnu11

SRC=$(filter-out ./src/test.c, $(wildcard ./src/*.c))

default: clean advcalc

clean :
	if [ -f $(EXEC) ] ; then rm $(EXEC) ; fi
	
advcalc: 
	$(CC) $(SRC) $(BUILD_CFLAGS)

debug: 
	$(CC) $(SRC) $(DEBUG_CFLAGS)


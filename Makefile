INCLUDE_DIR=./include/
EXEC=advcalc
CC=gcc-12
CFLAGS=-I $(INCLUDE_DIR) -o $(EXEC) 
SRC=$(wildcard ./src/*.c)


clean :
	rm $(EXEC)

advcalc:  
	$(CC) $(SRC) $(CFLAGS)



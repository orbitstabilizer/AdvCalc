INCLUDE_DIR=./include/
SRC_DIR=./src/
EXEC=advcalc
BIN_DIR=./bin/
CC=gcc
BUILD_CFLAGS=--std=gnu11 -I $(INCLUDE_DIR)
DEBUG_CFLAGS=-Wall -Wextra  -pedantic -fsanitize=address -g

SRC=$(filter-out $(SRC_DIR)test.c, $(wildcard $(SRC_DIR)*.c))
OBJ=$(patsubst $(SRC_DIR)%.c, $(BIN_DIR)%.o, $(SRC))

advcalc: $(OBJ)
	$(CC) $^ -o $(EXEC) $(BUILD_CFLAGS) 

debug: BUILD_CFLAGS += $(DEBUG_CFLAGS)
debug: advcalc

# create_bin_dir:
# 	if [ ! -d $(BIN_DIR) ] ; then mkdir $(BIN_DIR) ; fi

$(BIN_DIR)%.o: $(SRC_DIR)%.c #create_bin_dir
	if [ ! -d $(BIN_DIR) ] ; then mkdir $(BIN_DIR) ; fi
	$(CC) -c $< -o $@ $(BUILD_CFLAGS)

clean:
	if [ -f $(EXEC) ] ; then rm $(EXEC) ; fi
	if [ -d $(BIN_DIR) ] ; then rm -r $(BIN_DIR)/* ; fi







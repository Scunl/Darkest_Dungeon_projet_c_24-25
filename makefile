CC = gcc
CFLAGS = -Wall -Iinclude -g
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
EXEC = main

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)

distclean: clean
	rm -rf $(EXEC)

.PHONY: clean distclean
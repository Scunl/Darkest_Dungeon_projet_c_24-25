TARGET = bin/darkest_dungeon

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

CC = gcc
CFLAGS = -Wall -Wextra -g -I$(INC_DIR)
LDFLAGS =

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Compilation terminée : $(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilé : $< -> $@"

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Nettoyage terminé."

rebuild: clean all

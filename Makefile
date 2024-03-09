# Directories
SRC_DIR = src
INC_DIR = $(SRC_DIR)/inc
LIB_DIR = lib
UT_DIR = $(LIB_DIR)/Unity/src
BUILD_DIR = bld
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Toolchain
CC = gcc
DEBUG = gdb

# Files
TARGET = $(BIN_DIR)/main
UTTARGET = $(BIN_DIR)/unittest
SOURCE = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCE))

# Flags
CFLAGS = -I$(INC_DIR)
WFLAGS = -Wall -Werror -Wextra -Wshadow
UTFLAGS = -L$(UT_DIR)

# Building
#- Linking
$(TARGET): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@

#- Linking
$(UTTARGET): $(OBJECTS)
	@mkdir -p $(dir $(TARGET))
	$(CC) $(OBJECTS) $(UTFLAGS) -o $(UTTARGET)

#- Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@



.PHONY: all clean test run

all: $(TARGET) $(UTTARGET)

clean:
	rm -rf $(BUILD_DIR)

test: $(UTTARGET)
	./$(UTTARGET)

run: $(TARGET)
	./$(TARGET)
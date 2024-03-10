# Directories
SRC_DIR = src
INC_DIR = $(SRC_DIR)/inc
LIB_DIR = lib
BUILD_DIR = bld
TEST_DIR = test
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
UT_DIR = $(LIB_DIR)/Unity/src
TEST_OBJ_DIR = $(BUILD_DIR)/test_obj
TEST_BIN_DIR = $(BUILD_DIR)/test_bin

# Toolchain
CC = gcc
CC_test = gcc -DUNITTEST
DEBUG = gdb

# Files
# - src, obj, and target
TARGET = $(BIN_DIR)/main
SOURCE = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCE))
# - testing src, obj, and target
UTTARGET = $(TEST_BIN_DIR)/unittest
TEST_SOURCE = $(wildcard $(TEST_DIR)/*.c)
UT_TEST_SOURCE = $(wildcard $(UT_DIR)/*.c)
TEST_SRC_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(filter-out $(SRC_DIR)/main.c, $(SOURCE)))
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(TEST_SOURCE))
UT_TEST_OBJECTS = $(patsubst $(UT_DIR)/%.c,$(TEST_OBJ_DIR)/%.o,$(UT_TEST_SOURCE))

# Flags
CFLAGS = -I$(INC_DIR)
WFLAGS = -Wall -Werror -Wextra -Wshadow
UTFLAGS = -I$(UT_DIR)

# Building
#- Linking
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ -o $@

# $(UTTARGET): $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS)) $(TEST_OBJECTS) $(UT_TEST_OBJECTS) 
$(UTTARGET): $(TEST_OBJECTS) $(UT_TEST_OBJECTS) $(TEST_SRC_OBJECTS)
	@mkdir -p $(TEST_BIN_DIR)
	$(CC_test) $^ -o $(UTTARGET)

#- Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC_test) $(CFLAGS) $(UTFLAGS) -c $^ -o $@

$(TEST_OBJ_DIR)/%.o: $(filter-out $(SRC_DIR)/main.c, $(SRC_DIR))/%.c
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC_test) $(CFLAGS) $(UTFLAGS) -c $^ -o $@

$(TEST_OBJ_DIR)/%.o: $(UT_DIR)/%.c
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC_test) $(CFLAGS) $(UTFLAGS) -c $^ -o $@


.PHONY: all clean test run

all: $(TARGET) $(UTTARGET)

clean:
	rm -rf $(BUILD_DIR)

test: $(UTTARGET)
	./$(UTTARGET)

run: $(TARGET)
	./$(TARGET)
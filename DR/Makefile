# Variables
CC = gcc
CFLAGS = -Wall
SRC_DIR = $(CHAPTER)/src
INCLUDE_DIR = $(CHAPTER)/include
BIN_DIR = $(CHAPTER)/bin
OBJ_DIR = $(CHAPTER)/obj

# Add include directory for the chapter
INCLUDE_FLAG = -I$(INCLUDE_DIR)

# Collect all .c files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXES = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

# Declare phony targets
.PHONY: all clean dirs chapter1 chapter2 chapter3 chapter4 run

# Default target (must define a chapter target like 'make chapter1')
all: $(EXES)

# Rule to compile each .c file into an executable in the bin folder
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(INCLUDE_DIR)/error_handling.o
	$(CC) $(CFLAGS) $(INCLUDE_FLAG) -o $@ $^

# Rule to compile each .c file into an object file in the obj folder
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE_FLAG) -c $< -o $@

# Rule to compile error_handling.c
$(INCLUDE_DIR)/error_handling.o: $(INCLUDE_DIR)/error_handling.c
	$(CC) $(CFLAGS) $(INCLUDE_FLAG) -c $< -o $@

# Create necessary directories if they don't exist
dirs:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)

# Clean up object and executable files
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/* $(INCLUDE_DIR)/error_handling.o

# Chapter-specific targets
chapter1:
	$(MAKE) CHAPTER=164992_chapter1 dirs all

chapter2:
	$(MAKE) CHAPTER=164992_chapter2 dirs all

chapter3:
	$(MAKE) CHAPTER=164992_chapter3 dirs all

chapter4:
	$(MAKE) CHAPTER=164992_chapter4 dirs all

chapter5:
	$(MAKE) CHAPTER=164992_chapter5 dirs all

chapter6:
	$(MAKE) CHAPTER=164992_chapter6 dirs all

chapter7:
	$(MAKE) CHAPTER=164992_chapter7 dirs all

chapter8:
	$(MAKE) CHAPTER=164992_chapter8 dirs all

# Run a specific executable in the current chapter's bin directory
run:
	@$(if $(CHAPTER),, $(error CHAPTER not set, run like 'make run CHAPTER=164992_chapter1 EXE=<name_of_exe>'))
	@$(if $(EXE),, $(error EXE not set, run like 'make run CHAPTER=164992_chapter1 EXE=<name_of_exe>'))
	./$(CHAPTER)/bin/$(EXE)


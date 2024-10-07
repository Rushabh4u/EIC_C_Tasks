# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Werror -Wall -I.

# Common source files
COMMON_SRC = error_handling.c error_handling.h

# Function to extract all .c files in a given directory
SRC_DIR = $(DIR)

# Function to remove all exe files in the current directory.
EXE_FILES = $(wildcard *.out)

# Default target
all: $(EXE)

# Rule to compile all .c files in the specified directory along with common files
$(EXE): $(SRC_DIR) $(COMMON_SRC)
	$(CC) $(CFLAGS) -o $(EXE) $^ -lm
	
# Rule to run the generated executable
run:
	./$(EXE)

# Clean target
clean: $(EXE_FILES)
	rm -f $(EXE_FILES)




# To compile an exercise, you need to specify the directory containing the .c files 
# and the name of the output executable when invoking make. 
# For example:

# Command ---> make DIR=chapter1/Exercise_1.1 EXE=Exercise_1_1

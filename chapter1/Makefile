# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Wall -Werror -Wextra 

# Common source files

# Function to extract all .c files in a given directory
SRC_DIR = $(wildcard $(DIR)/*.c $(DIR)/*.h)

# Default target
all: $(EXE) run

# Rule to compile all .c files in the specified directory along with common files
$(EXE): $(SRC_DIR) 
	$(CC) $(CFLAGS) -o $(EXE) $^
	
# Rule to run the generated executable
run: $(EXE)
	./$(EXE)

# Clean target
clean:
	rm -f $(EXE)




# To compile an exercise, you need to specify the directory containing the .c files 
# and the name of the output executable when invoking make. 
# For example:

# Command ---> make DIR=chapter1/Exercise_1.1 EXE=Exercise_1_1

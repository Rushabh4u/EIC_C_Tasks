# Compiler
CC = gcc

# Compilation flags
CFLAGS = -Wall -O2

# Targets
TARGETS = simpcat1 simpcat2 simpcat3 simpcat4 simpcat5

# Default target: build all executables
all: $(TARGETS)

# Build rules for each simpcat program
simpcat1: simpcat1.c
	$(CC) $(CFLAGS) -o $@ $<

simpcat2: simpcat2.c
	$(CC) $(CFLAGS) -o $@ $<

simpcat3: simpcat3.c
	$(CC) $(CFLAGS) -o $@ $<

simpcat4: simpcat4.c
	$(CC) $(CFLAGS) -o $@ $<

simpcat5: simpcat5.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean up build artifacts
clean:
	rm -f $(TARGETS) *.o


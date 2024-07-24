# Targets 
# target: prerequisites
#\t commands

# The commands are a series of steps typically to make the target, 
# need to start with a tab character, no spaces
# The prerequisites are file names, swparated by spaces.
# These files need to exist before the commands for the target are run.

gc = gcc
gdbflag = -g
exeflag = -o

# Should be equivalant to your list of C files, if you don't build selectively

SRC = $(wildcard *.c *.h)

oput: output
	@echo "Execution started..."	#Message to terminal
	@./$@


output: ${SRC}
	@$(gc) $(gdbflag) $^ $(exeflag) oput

	
# clean is often used as a target that removes the output of other targets.
clean:
	rm -f *.o

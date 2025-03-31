/*
 * Program: File Concatenation
 * Author: Rushabh Goswami
 * Created Date: 21/12/24
 * Description: This program emulates the functionality of the `cat` command in UNIX/Linux.
 * 				It reads data from files (or standard input if no files are specified)
 *				and writes the data to standard output. It uses system calls for file
 *				operations and includes robust error handling.
 */

/* Required header files */
#include <fcntl.h>  /* For open system call */
#include <stdarg.h> /* For variable argument functions */
#include <stdio.h>  /* For standard I/O operations */
#include <stdlib.h> /* For exit and other utility functions */
#include <unistd.h> /* For read, write, and close system calls */

/* Constant definitions */
#define STDIN 0   /* File descriptor for standard input */
#define STDOUT 1  /* File descriptor for standard output */
#define STDERR 2  /* File descriptor for standard error */

/* Function prototypes */
void error(char *fmt, ...);        /* Print an error message and exit */
void filecopy(int ifd, int ofd);   /* Copy data from input to output */

/*
 * error: Print an error message and terminate the program.
 * Arguments:
 *   fmt - Format string for the error message
 *   ... - Additional arguments for formatting
 * Description:
 *   This function uses a variable argument list to construct an error
 *   message and prints it to standard error before exiting the program.
 */
void error(char *fmt, ...) {
    va_list args;  /* Declare variable argument list */

    /* Initialize the variable argument list */
    va_start(args, fmt);

    /* Print error prefix and formatted message */
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    /* Clean up and terminate the program */
    va_end(args);
    exit(1);
}

/*
 * filecopy: Copy data from input file descriptor to output file descriptor.
 * Arguments:
 *   ifd - Input file descriptor
 *   ofd - Output file descriptor
 * Description:
 *   This function reads data from the input file descriptor in chunks
 *   and writes it to the output file descriptor. If an error occurs
 *   during writing, it terminates the program with an error message.
 */
void filecopy(int ifd, int ofd) {
    char buf[BUFSIZ];  /* Buffer to hold data chunks */
    ssize_t n;         /* Number of bytes read */

    /* Read from input and write to output until EOF is reached */
    while ((n = read(ifd, buf, BUFSIZ)) > 0) {
        if (write(ofd, buf, n) != n) {
            error("cat: write error");
        }
    }
}

/*
 * main: Entry point of the program.
 * Arguments:
 *   argc - Number of command-line arguments
 *   argv - Array of command-line argument strings
 * Returns:
 *   0 on successful execution, or terminates with an error.
 * Description:
 *   This function processes command-line arguments to determine the
 *   files to be concatenated. If no arguments are provided, it reads
 *   from standard input and writes to standard output.
 */
int main(int argc, char *argv[]) {
    int fd;  /* File descriptor for input files */

    if (argc == 1) {
        /* No files specified, copy from standard input to standard output */
        filecopy(STDIN, STDOUT);
    } else {
        /* Process each file specified in the command-line arguments */
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY)) == -1) {
                error("cat: can't open %s", *argv);
            } else {
                filecopy(fd, STDOUT);
                close(fd);  /* Close the file after processing */
            }
        }
    }
    return 0;  /* Successful program termination */
}


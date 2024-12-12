#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024  // Size of the buffer for reading

int main(int argc, char *argv[]) {
    int src_fd, dest_fd;        // File descriptors for source and destination files
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Check if both source and destination filenames are provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the source file for reading
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Open the destination file for writing (create if it doesn't exist, truncate if it does)
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(src_fd);  // Close source file before exiting
        exit(EXIT_FAILURE);
    }

    // Copy data from source file to destination file
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }

        // Check if all bytes were written
        if (bytes_written != bytes_read) {
            fprintf(stderr, "Error: Partial write occurred.\n");
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    // Check for read errors
    if (bytes_read == -1) {
        perror("Error reading from source file");
        close(src_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    // Close the files
    if (close(src_fd) == -1) {
        perror("Error closing source file");
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    if (close(dest_fd) == -1) {
        perror("Error closing destination file");
        exit(EXIT_FAILURE);
    }

    printf("File copied successfully from %s to %s\n", argv[1], argv[2]);
    return 0;
}


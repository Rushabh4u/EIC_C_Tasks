#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Create a new file (or overwrite if it exists) with write permissions
    fd = open("file_with_hole", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(1);
    }

    // Move the file pointer forward by 4 KB (4096 bytes) without writing data
    if (lseek(fd, 4096, SEEK_SET) == -1) {
        perror("Error seeking in file");
        close(fd);
        exit(1);
    }

    // Write a single byte to make the file allocation with a 4 KB hole
    if (write(fd, "A", 1) != 1) {
        perror("Error writing to file");
        close(fd);
        exit(1);
    }

    printf("File 'file_with_hole' created with a 4 KB hole.\n");

    close(fd);
    return 0;
}


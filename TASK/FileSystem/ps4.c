#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *c;
    int fd, sz;

    // Allocate memory for reading file content
    c = (char *) calloc(100, sizeof(char));
    if (c == NULL) {
        perror("calloc");
        exit(1);
    }

    // Open file in read-only mode
    fd = open("in1", O_RDONLY);
    if (fd < 0) {
        perror("open");
        free(c);
        exit(1);
    }

    // Read 10 bytes from the file
    sz = read(fd, c, 10);
    if (sz < 0) {
        perror("read");
        close(fd);
        free(c);
        exit(1);
    }

    printf("We have opened 'in1' and read %d bytes.\n", sz);
    c[sz] = '\0';
    printf("Content read: %s\n", c);

    // Check current offset with SEEK_CUR
    sz = lseek(fd, 0, SEEK_CUR);
    if (sz < 0) {
        perror("lseek");
        close(fd);
        free(c);
        exit(1);
    }
    printf("Current file offset: %d\n\n", sz);

    // Seek to the beginning of the file and read again
    lseek(fd, 0, SEEK_SET);
    sz = read(fd, c, 10);
    c[sz] = '\0';
    printf("After seeking to the beginning, read content: %s\n", c);

    // Seek 6 bytes back from the current position and read
    lseek(fd, -6, SEEK_CUR);
    sz = read(fd, c, 10);
    c[sz] = '\0';
    printf("After seeking back 6 bytes, read content: %s\n", c);

    // Attempt an invalid seek (SEEK_SET with negative offset)
    printf("Attempting to seek to a negative position.\n");
    sz = lseek(fd, -1, SEEK_SET);
    if (sz == -1) {
        perror("Invalid seek operation");
    }

    // Clean up
    close(fd);
    free(c);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <buffer size>\n", argv[0]);
        return 1;
    }

    int bufsize = atoi(argv[1]);
    char *c = malloc(bufsize * sizeof(char));
    if (!c) {
        perror("Failed to allocate buffer");
        return 1;
    }

    int i = 1;
    while (i > 0) {
        i = read(0, c, bufsize);
        if (i > 0) write(1, c, i);
    }

    free(c);
    return 0;
}


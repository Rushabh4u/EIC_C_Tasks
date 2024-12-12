#include <stdio.h>
#include <stdlib.h>

int main() {
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (fputc(ch, stdout) == EOF) {
            perror("fputc");
            exit(1);
        }
    }

    return 0;
}


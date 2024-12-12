#include <stdio.h>
#include <stdlib.h>

void print_file(FILE *fp) {
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (fputc(ch, stdout) == EOF) {
            perror("fputc");
            exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // No arguments provided, read from standard input
        print_file(stdin);
    } else {
        // Process each file provided as an argument
        for (int i = 1; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                perror(argv[i]);
                continue;
            }
            print_file(fp);
            fclose(fp);
        }
    }

    return 0;
}


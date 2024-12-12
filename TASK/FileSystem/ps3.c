#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void display_file_type(const struct stat *file_stat) {
    if (S_ISREG(file_stat->st_mode))
        printf("Regular file");
    else if (S_ISDIR(file_stat->st_mode))
        printf("Directory");
    else if (S_ISLNK(file_stat->st_mode))
        printf("Symbolic link");
    else if (S_ISCHR(file_stat->st_mode))
        printf("Character device");
    else if (S_ISBLK(file_stat->st_mode))
        printf("Block device");
    else if (S_ISFIFO(file_stat->st_mode))
        printf("FIFO (named pipe)");
    else if (S_ISSOCK(file_stat->st_mode))
        printf("Socket");
    else
        printf("Unknown type");
}

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char path[1024];

    // Check if directory name is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the directory
    dir = opendir(argv[1]);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Build the full path for the file
        snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);

        // Get file information
        if (stat(path, &file_stat) == -1) {
            perror("Error retrieving file info");
            continue;
        }

        // Print file name and type
        printf("%s: ", entry->d_name);
        display_file_type(&file_stat);
        printf("\n");
    }

    // Close the directory
    closedir(dir);

    return 0;
}


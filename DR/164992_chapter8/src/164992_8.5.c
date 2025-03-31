/*
 * Program: Modified fsize to print additional inode information
 * Author:  Rushabh Goswami
 * Created Date: 21/12/2024
 * Description: This program prints the file size, owner, and other inode information of files 
 *              and directories. It recursively traverses directories and prints details 
 *              for all files and subdirectories.
 */

/* Required header files */
#include <stdio.h>   /* For input/output functions */
#include <string.h>  /* For string manipulation functions */
#include <fcntl.h>   /* For file control options */
#include <sys/types.h> /* For defining data types used in system calls */
#include <sys/stat.h>  /* For file status information */
#include <stdlib.h>  /* For general utilities (malloc, free, etc.) */
#include <dirent.h>  /* For directory operations */
#include <pwd.h>     /* For user information (getpwuid) */

/* Constant definitions */
#define MAX_PATH 1024  /* Maximum length for path names */
#ifndef DIRSIZ
#define DIRSIZ 14      /* Default directory entry size */
#endif

/* Function to recursively walk through directories */
void dirwalk(char *dir, void (*fcn)(char *)) {
    char name[MAX_PATH];     /* Array to store the full file path */
    struct dirent *dp;       /* Directory entry structure */
    DIR *dfd;                /* Directory stream */

    /* Open the directory */
    if ((dfd = opendir(dir)) == NULL) {
        puts("Error: Cannot open Directory");
        return;
    }

    puts(dir); /* Print the directory name */

    /* Process each directory entry */
    while ((dp = readdir(dfd)) != NULL) {
        /* Skip '.' and '..' directories */
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        /* Check if the full path exceeds the buffer size */
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            puts("Error: Name too long!");
        else {
            /* Construct the full path and call fsize */
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }

    /* Close the directory stream */
    closedir(dfd);
}

/* Function to print file size and other inode information */
void fsize(char *name) {
    struct stat stbuf; /* Structure to hold file status information */

    /* Get the file stats using stat system call */
    if (stat(name, &stbuf) == -1) {
        puts("Error: Cannot get file stats!");
        return;
    }

    /* If the entry is a directory, recursively walk through it */
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
        dirwalk(name, fsize);
    }

    /* Get the owner information using getpwuid function */
    struct passwd *pwd = getpwuid(stbuf.st_uid);

    /* Print file name, size, and owner */
    printf("%81d %s Owner: %s\n", (int)stbuf.st_size, name, pwd->pw_name);
}

/* Main function */
int main(int argc, char *argv[]) {
    /* If no arguments are passed, process the current directory */
    if (argc == 1)
        fsize(".");
    else
        /* Otherwise, process each file/directory passed as an argument */
        while (--argc > 0)
            fsize(*++argv);

    return 0; /* Exit the program successfully */
}


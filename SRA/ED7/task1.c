/*
*Command to run this program:
*	./task1 file1.txt file2.txt
*
*Created by Rushabh Goswami
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *args[]) {
    /* 
    Ensure the correct number of arguments (program name + 2 file names).
    If not, print usage information and exit with an error code.
    */
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", args[0]);
        return 1;
    }

    /* 
    Open both files for reading. If any of the files fail to open,
    print an error message and exit with an error code.
    */
    FILE *file1 = fopen(args[1], "r");
    FILE *file2 = fopen(args[2], "r");
    
    if (file1 == NULL || file2 == NULL) {
        printf("Error opening one of the files.\n");
        return 1;
    }

    /* 
    Declare buffers to hold lines from both files and variables
    to keep track of the line number and the number of differences.
    */
    char cLineOf1[256];
    char cLineOf2[256];
    int iLine = 1;
    int iDifferenceCount = 0;

    /* 
    Compare lines from both files. Use `fgets` to read each line
    from both files and `strcmp` to compare them.
    If the lines are different, print the line numbers and contents.
    */
    while (fgets(cLineOf1, sizeof(cLineOf1), file1) && fgets(cLineOf2, sizeof(cLineOf2), file2)) {
        if (strcmp(cLineOf1, cLineOf2) != 0) {
            iDifferenceCount++;
            printf("-------------------------\n");
            printf("Line %d has not matched!\n", iLine);
            printf("Line of %s: %s", args[1], cLineOf1);
            printf("Line of %s: %s", args[2], cLineOf2);
            printf("-------------------------\n\n");

            /* 
            Stop printing differences after 10 mismatches to avoid excessive output.
            */
            if (iDifferenceCount >= 10) {
                printf("Stopped printing after 10 differences.\n");
                break;
            }
        }
        iLine++;
    }

    /* 
    Check if one file has additional lines beyond the other.
    If file1 has more lines than file2, print the remaining lines
    from file1 that have no corresponding lines in file2.
    */
    while (fgets(cLineOf1, sizeof(cLineOf1), file1)) {
        iDifferenceCount++;
        printf("-------------------------\n");
        printf("Line %d has not matched!\n", iLine);
        printf("Line of %s: %s", args[1], cLineOf1);
        printf("Line of %s: (No matching line)\n", args[2]);
        printf("-------------------------\n\n");
        iLine++;

        /* 
        Stop printing differences after 10 mismatches to avoid excessive output.
        */
        if (iDifferenceCount >= 10) {
            printf("Stopped printing after 10 differences.\n");
            break;
        }
    }

    /* 
    If file2 has more lines than file1, print the remaining lines
    from file2 that have no corresponding lines in file1.
    */
    while (fgets(cLineOf2, sizeof(cLineOf2), file2)) {
        iDifferenceCount++;
        printf("-------------------------\n");
        printf("Line %d has not matched!\n", iLine);
        printf("Line of %s: (No matching line)\n", args[1]);
        printf("Line of %s: %s", args[2], cLineOf2);
        printf("-------------------------\n\n");
        iLine++;

        /* 
        Stop printing differences after 10 mismatches to avoid excessive output.
        */
        if (iDifferenceCount >= 10) {
            printf("Stopped printing after 10 differences.\n");
            break;
        }
    }

    /* 
    If no differences were found, print that the files are identical.
    */
    if (iDifferenceCount == 0) {
        printf("The files are Same.\n");
    }

    /* 
    Close both files before exiting the program.
    */
    fclose(file1);
    fclose(file2);
    
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For tolower()

/* Constants for bit positions */
#define READ_ONLY 0x01
#define HIDDEN    0x02
#define SYSTEM    0x04
#define VOLUME    0x08
#define DIRECTORY 0x10
#define ARCHIVE   0x20

typedef struct {
    char filename[8];  /* 8 bytes for the filename */
    char extension[3]; /* 3 bytes for the extension */
    unsigned char attribute; /* 1 byte for the attributes */
    char reserved[10]; /* Reserved 10 bytes */
    unsigned short time; /* 2 bytes for time */
    unsigned short date; /* 2 bytes for date */
    unsigned short startCluster; /* 2 bytes for starting cluster number */
    unsigned long size; /* 4 bytes for the file size */
} DirectoryEntry;

void displayAttributes(unsigned char attribute) {
    int hasAttributes = 0;
    printf("Current Attributes:\n");
    if (attribute & READ_ONLY) { printf("  Read-only\n"); hasAttributes = 1; }
    if (attribute & HIDDEN)    { printf("  Hidden\n"); hasAttributes = 1; }
    if (attribute & SYSTEM)    { printf("  System\n"); hasAttributes = 1; }
    if (attribute & VOLUME)    { printf("  Volume label\n"); hasAttributes = 1; }
    if (attribute & DIRECTORY) { printf("  Directory\n"); hasAttributes = 1; }
    if (attribute & ARCHIVE)   { printf("  Archive\n"); hasAttributes = 1; }

    if (!hasAttributes) {
        printf("  (No attributes set)\n");
    }
    printf("\n");
}

void modifyAttributes(unsigned char *attribute) {
    char choice[3]; // Buffer for input (including newline and null terminator)

    printf("Modify Attributes:\n");

    printf("Set Read-only? (y/n): ");
    fgets(choice, sizeof(choice), stdin);
    if (tolower(choice[0]) == 'y') *attribute |= READ_ONLY;
    else *attribute &= ~READ_ONLY;

    printf("Set Hidden? (y/n): ");
    fgets(choice, sizeof(choice), stdin);
    if (tolower(choice[0]) == 'y') *attribute |= HIDDEN;
    else *attribute &= ~HIDDEN;

    printf("Set System? (y/n): ");
    fgets(choice, sizeof(choice), stdin);
    if (tolower(choice[0]) == 'y') *attribute |= SYSTEM;
    else *attribute &= ~SYSTEM;

    printf("Set Volume Label? (y/n): ");
    fgets(choice, sizeof(choice), stdin);
    if (tolower(choice[0]) == 'y') *attribute |= VOLUME;
    else *attribute &= ~VOLUME;

    printf("Set Archive? (y/n): ");
    fgets(choice, sizeof(choice), stdin);
    if (tolower(choice[0]) == 'y') *attribute |= ARCHIVE;
    else *attribute &= ~ARCHIVE;

    printf("\n");
}

int main() {
    DirectoryEntry dirEntry;
    FILE *file;

    /* Open file representing the directory (simulation) */
    file = fopen("directory.dat", "rb+");
    if (file == NULL) {
        printf("Error opening directory file.\n");
        return 1;
    }

    /* Read the first directory entry */
    if (fread(&dirEntry, sizeof(DirectoryEntry), 1, file) != 1) {
        printf("Error reading directory entry.\n");
        fclose(file);
        return 1;
    }

    /* Display current attributes */
    printf("Filename: %.8s.%.3s\n", dirEntry.filename, dirEntry.extension);
    displayAttributes(dirEntry.attribute);

    /* Modify attributes interactively */
    modifyAttributes(&dirEntry.attribute);

    /* Write back updated attributes */
    fseek(file, 0, SEEK_SET); /* Go to the beginning */
    if (fwrite(&dirEntry, sizeof(DirectoryEntry), 1, file) != 1) {
        printf("Error writing directory entry.\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    printf("Attributes updated successfully.\n");

    return 0;
}

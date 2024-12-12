#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_ONLY 0x01
#define HIDDEN    0x02
#define SYSTEM    0x04
#define VOLUME    0x08
#define DIRECTORY 0x10
#define ARCHIVE   0x20

typedef struct {
    char filename[8];
    char extension[3];
    unsigned char attribute;
    char reserved[10];
    unsigned short time;
    unsigned short date;
    unsigned short startCluster;
    unsigned long size;
} DirectoryEntry;

void displayAttributes(unsigned char attribute) {
    printf("Current Attributes:\n");
    if (attribute & READ_ONLY) printf("  Read-only\n");
    if (attribute & HIDDEN)    printf("  Hidden\n");
    if (attribute & SYSTEM)    printf("  System\n");
    if (attribute & VOLUME)    printf("  Volume label\n");
    if (attribute & DIRECTORY) printf("  Directory\n");
    if (attribute & ARCHIVE)   printf("  Archive\n");
    printf("\n");
}

void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void modifyAttributes(unsigned char *attribute) {
    char choice;
    printf("Modify Attributes:\n");

    printf("Set Read-only? (y/n): ");
    scanf(" %c", &choice);
    flushInput();
    if (choice == 'y' || choice == 'Y') *attribute |= READ_ONLY;
    else *attribute &= ~READ_ONLY;

    printf("Set Hidden? (y/n): ");
    scanf(" %c", &choice);
    flushInput();
    if (choice == 'y' || choice == 'Y') *attribute |= HIDDEN;
    else *attribute &= ~HIDDEN;

    printf("Set System? (y/n): ");
    scanf(" %c", &choice);
    flushInput();
    if (choice == 'y' || choice == 'Y') *attribute |= SYSTEM;
    else *attribute &= ~SYSTEM;

    printf("Set Volume Label? (y/n): ");
    scanf(" %c", &choice);
    flushInput();
    if (choice == 'y' || choice == 'Y') *attribute |= VOLUME;
    else *attribute &= ~VOLUME;

    printf("Set Archive? (y/n): ");
    scanf(" %c", &choice);
    flushInput();
    if (choice == 'y' || choice == 'Y') *attribute |= ARCHIVE;
    else *attribute &= ~ARCHIVE;

    printf("\n");
}

int main() {
    DirectoryEntry dirEntry;
    FILE *file;

    file = fopen("directory.dat", "rb+");
    if (file == NULL) {
        printf("Error opening directory file.\n");
        return 1;
    }

    if (fread(&dirEntry, sizeof(DirectoryEntry), 1, file) != 1) {
        printf("Error reading directory entry.\n");
        fclose(file);
        return 1;
    }

    printf("Filename: %.8s.%.3s\n", dirEntry.filename, dirEntry.extension);
    displayAttributes(dirEntry.attribute);

    modifyAttributes(&dirEntry.attribute);

    fseek(file, 0, SEEK_SET);
    if (fwrite(&dirEntry, sizeof(DirectoryEntry), 1, file) != 1) {
        printf("Error writing directory entry.\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    printf("Attributes updated successfully.\n");

    return 0;
}


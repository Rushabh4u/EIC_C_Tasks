#include <stdio.h>

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

int main() {
    DirectoryEntry entry = {
        "TESTFILE", // 8 characters (padded if shorter)
        "TXT",      // 3 characters (padded if shorter)
        0x00,       // No attributes set initially
        "",         // Reserved space (not used)
        0,          // Time placeholder
        0,          // Date placeholder
        1,          // Starting cluster
        1024        // File size in bytes
    };

    FILE *file = fopen("directory.dat", "wb");
    if (file == NULL) {
        printf("Error creating file.\n");
        return 1;
    }

    fwrite(&entry, sizeof(DirectoryEntry), 1, file);
    fclose(file);

    printf("File created successfully.\n");
    return 0;
}


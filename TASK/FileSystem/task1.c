#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOG_FILE "/home/harsh0412/164990_Harsh_Jangid_Cprogramming/Class_Tasks/FileSystem/logfile"

void write_to_fill_log() {
    char *username;
    long t;
    FILE *f;

    username = getenv("USER");
    t = time(0);

    f = fopen(LOG_FILE, "a");
    if (f == NULL) {
        perror("Error opening log file");
        return;
    }

    fprintf(f, "%s %ld\n", username ? username : "Unknown", t);
    fclose(f);
}

int main ()
{
write_to_fill_log();
}

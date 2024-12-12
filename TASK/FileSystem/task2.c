#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <string.h>

#define LOG_FILE "/home/harsh0412/164990_Harsh_Jangid_Cprogramming/Class_Tasks/FileSystem/logfile"

void write_to_fill_log() {
    char *username;
    long t;
    int fd;
    char log_entry[256];

    username = getenv("USER");
    t = time(0);

    // Open the file with O_APPEND and O_SYNC for synchronized and atomic append
    fd = open(LOG_FILE, O_WRONLY | O_APPEND | O_SYNC);
    if (fd == -1) {
        perror("Error opening log file");
        return;
    }

    // Lock the file for exclusive access
    if (flock(fd, LOCK_EX) != 0) {
        perror("Error locking log file");
        close(fd);
        return;
    }

    // Format the log entry with username and timestamp
    snprintf(log_entry, sizeof(log_entry), "%s %ld\n", username ? username : "Unknown", t);

    // Write log entry to the file
    if (write(fd, log_entry, strlen(log_entry)) == -1) {
        perror("Error writing to log file");
    }

    // Unlock the file
    if (flock(fd, LOCK_UN) != 0) {
        perror("Error unlocking log file");
    }

    close(fd);
}

int main ()
{
write_to_fill_log();
}

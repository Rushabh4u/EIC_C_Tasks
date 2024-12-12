#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>

typedef struct {
  clock_t clock_val;
  time_t time_val;
  struct timeval gettime_val;
  struct tms times_val;
} all_times;

// Function to retrieve and store current time values in various formats
void get_time(all_times *t)
{
  t->clock_val = clock();                 // Get processor time used by the program
  t->time_val = time(NULL);               // Get current calendar time (seconds since epoch)
  gettimeofday(&(t->gettime_val), NULL);  // Get more precise time (seconds and microseconds)
  times(&(t->times_val));                 // Get process times (user and system time)
}

// Function to print the time durations between two `all_times` structures
void print_duration(all_times *t1, all_times *t2)
{
  float elapsed;
  long clktck, nticks;

  nticks = t2->clock_val - t1->clock_val;                  // Difference in processor time (in clock ticks)
  elapsed = (float)nticks / CLOCKS_PER_SEC;                // Convert clock ticks to seconds
  fprintf(stderr, "clock: %f sec\n", elapsed);

  nticks = t2->time_val - t1->time_val;                    // Difference in calendar time (seconds)
  fprintf(stderr, "time: %d sec\n", nticks);

  elapsed = t2->gettime_val.tv_sec - t1->gettime_val.tv_sec;  // Difference in seconds
  elapsed += (t2->gettime_val.tv_usec - t1->gettime_val.tv_usec) / 1e6; // Add difference in microseconds
  fprintf(stderr, "gettimeofday: %f sec\n", elapsed);

  clktck = sysconf(_SC_CLK_TCK);                           // Number of clock ticks per second (system dependent)
  nticks = t2->times_val.tms_utime - t1->times_val.tms_utime;  // User CPU time used
  elapsed = (float)nticks / clktck;                        // Convert ticks to seconds
  fprintf(stderr, "times: %f sec user time\n", elapsed);

  nticks = t2->times_val.tms_stime - t1->times_val.tms_stime;  // System CPU time used
  elapsed = (float)nticks / clktck;                        // Convert ticks to seconds
  fprintf(stderr, "times: %f sec system time\n", elapsed);
}

// Function to read from standard input and write to standard output byte by byte
long simplecat()
{
  char c;
  int i;
  long cnt = 0;

  i = fread(&c, 1, 1, stdin);            // Read 1 byte from stdin
  while (i > 0) {
    fwrite(&c, 1, 1, stdout);            // Write 1 byte to stdout
    i = fread(&c, 1, 1, stdin);          // Read the next byte
    cnt++;                               // Count each byte processed
  }

  return cnt;                            // Return the total number of bytes processed
}

int main(void)
{
  int totalbytes;

  all_times a1, a2;

  get_time(&a1);                         // Record start time

  totalbytes = simplecat();              // Process all bytes from stdin to stdout

  get_time(&a2);                         // Record end time
  print_duration(&a1, &a2);              // Print elapsed time statistics

  fprintf(stderr, "total of %f MiB\n", totalbytes / 1e6); // Output total bytes processed in MB

  return 0;
}


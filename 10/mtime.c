#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define BUF_SIZE 1000

int main() {
  struct timeval *tv;
  time_t t;
  char *s;
  struct tm *gmt;
  struct tm *local;
  time_t mk;
  clock_t clk = clock();

  tv = (struct timeval*) malloc(BUF_SIZE);
  gettimeofday(tv, NULL); // returns calendar time to tv
  printf("gettimeofday: %ld\n", (long) tv->tv_sec);

  t = time(NULL); // time since Epoch 1970-01-01 00:00:00 +0000 (UTC)
		  // would be the same as gettimeofday->tv_sec
  printf("time: %ld\n", (long) t);

  s = (char *) malloc(BUF_SIZE);
  ctime_r(&t, s);
  printf("ctime: %s", ctime(&t)); // printable time including newline and null terminating, statically allocated

  /*
   * Converts a calendar time into a broken-down time
   */
  gmt = (struct tm*) malloc(BUF_SIZE);
  gmtime_r(&t, gmt); // UTC 
  printf("[UTC] Sec:%d Min:%d Hour:%d Day:%d Month:%d Year:%d\n",
      gmt->tm_sec,
      gmt->tm_min,
      gmt->tm_hour,
      gmt->tm_mday,
      gmt->tm_mon,
      gmt->tm_year);

  local = (struct tm*) malloc(BUF_SIZE);
  localtime_r(&t, local); // system's local time
  printf("[LOCAL] Sec:%d Min:%d Hour:%d Day:%d Month:%d Year:%d\n",
      local->tm_sec,
      local->tm_min,
      local->tm_hour,
      local->tm_mday,
      local->tm_mon,
      local->tm_year);

  mk = mktime(local); // broken-down time to time_t
  printf("mktime: %ld\n", (long) mk);
  
  /*
   * Process time
   */
  printf("clock: %ld\n", (long) clk);
  printf("CLOCKS_PER_SEC: %ld\n", (long) CLOCKS_PER_SEC);
  printf("clock (divided): %ld\n", (long) clk / CLOCKS_PER_SEC);

  return 0;
}

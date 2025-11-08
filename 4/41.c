#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1000

int main(int argc, char **argv) {
  char *buf = (char *) malloc(BUFSIZE);
  char *fname;
  int opt;
  int aflag;
  int res;
  int fd;

  while ((res = read(0, buf, BUFSIZE)) > 0) {
    if (res == -1) {
      fprintf(stderr, "Error caught when reading from stdin: %d", errno);
      exit(EXIT_FAILURE);    
    }

    while (res < BUFSIZE && buf[res] != '\0') {
      buf[res++] = '\0';
    }

    while ((opt = getopt(argc, argv, "a")) != -1) {
      switch (opt) {
        case 'a':
          aflag = 1;
          break;
        case '?':
          fprintf(stderr, "Usage: %s [-a] [FILE]...\n", argv[0]);
          exit(EXIT_FAILURE);
      }
    }

    printf("%s", buf);

    while (optind < argc) {
      fname = argv[optind];

      fd = open(fname, O_WRONLY | (aflag == 1 ? O_APPEND : O_TRUNC) | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
      if (res == -1) {
        fprintf(stderr, "Error caught when opening %s: errno=%d\n", fname, errno);
        exit(EXIT_FAILURE);
      }

      res = write(fd, buf, BUFSIZE);
      if (res == -1) {
        fprintf(stderr, "Error caught when writing to %s: errno=%d\n", fname, errno);
        exit(EXIT_FAILURE);
      }

      res = close(fd);
      if (res == -1) {
        fprintf(stderr, "Error caught when closing %s: errno=%d\n", fname, errno);
        exit(EXIT_FAILURE);
      }

      optind++;
    }
  }

  return 0;
}

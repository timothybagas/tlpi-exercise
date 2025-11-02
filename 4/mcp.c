#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1000

int main(int argc, char **argv) {
  int res, fd1, fd2;
  char *fname1, *fname2;
  char *buf = malloc(BUFSIZE);

  fname1 = argv[1];
  fd1 = open(fname1, O_RDONLY);
  if (fd1 == -1) {
    fprintf(stderr, "Error caught when opening %s: %d", fname1, errno);
    exit(EXIT_FAILURE);
  }


  fname2 = argv[2];
  fd2 = open(fname2, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
  if (fd2 == -1) {
    fprintf(stderr, "Error caught when opening %s: %d", fname2, errno);
    exit(EXIT_FAILURE);
  }

  while ((res = read(fd1, buf, BUFSIZE)) > 0) {
    if (res == -1) {
      fprintf(stderr, "Error caught when reading from %s: %d", fname1, errno);
      exit(EXIT_FAILURE);
    }

    while (res < BUFSIZE && buf[res] != '\0') {
      buf[res++] = '\0';
    }

    res = write(fd2, buf, BUFSIZE);
    if (res == -1) {
      fprintf(stderr, "Error caught when writing to %s: errno=%d\n", fname2, errno);
      exit(EXIT_FAILURE);
    }
  }

  res = close(fd1);
  if (res == -1) {
    fprintf(stderr, "Error caught when closing %s: %d", fname1, errno);
    exit(EXIT_FAILURE);
  }

  res = close(fd2);
  if (res == -1) {
    fprintf(stderr, "Error caught when closing %s: %d", fname2, errno);
    exit(EXIT_FAILURE);
  }
  return 0;
}

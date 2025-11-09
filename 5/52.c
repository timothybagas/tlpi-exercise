#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd;
  off_t off;

  fd = open("test", O_WRONLY | O_APPEND, S_IRWXU);
  if (fd == -1) {
    fprintf(stderr, "open");
    exit(EXIT_FAILURE);
  }

  off = lseek(fd, 0, SEEK_SET);
  if (off == -1) {
    fprintf(stderr, "lseek");
    exit(EXIT_FAILURE);
  }

  if (write(fd, "timi", 4) == -1) {
    fprintf(stderr, "write");
    exit(EXIT_FAILURE);
  }

  return 0;
}

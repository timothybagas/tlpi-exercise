#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd, nbytes, x;

  nbytes = atoi(argv[2]);
  if (!nbytes) {
    fprintf(stderr, "atoi");
    exit(EXIT_FAILURE);
  }

  x = (argc == 4) && (*argv[3] == 'x');
  fd = open(argv[1], O_WRONLY | O_CREAT | (x ? 0 : O_APPEND), S_IRWXU);
  if (fd == -1) {
    fprintf(stderr, "open");
    exit(EXIT_FAILURE);
  }

  while (nbytes >= 1) {
    if (x && lseek(fd, 0, SEEK_END) == -1) {
      fprintf(stderr, "lseek");
      exit(EXIT_FAILURE);
    }
    if (write(fd, " ", 1) == -1) {
      fprintf(stderr, "write");
      exit(EXIT_FAILURE);
    }
    nbytes--;
  }
  
  if (close(fd) ==  -1) {
    fprintf(stderr, "close");
    exit(EXIT_FAILURE);
  }

  return 0;
}

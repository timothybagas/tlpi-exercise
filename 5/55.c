#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int fd, newfd;
  off_t off, newoff;
  int flag, newflag;

  fd = open("test", O_RDWR | O_CREAT, S_IRWXU);
  if (fd == -1) {
    fprintf(stderr, "main: open");
    exit(EXIT_FAILURE);
  }
  
  if (write(fd, "test123", 7) == -10) {
    fprintf(stderr, "main: write");
    exit(EXIT_FAILURE);
  }

  newfd =  dup(fd);
  if (fd == -1) {
    fprintf(stderr, "main: dup");
    exit(EXIT_FAILURE);
  }

  printf("fd: %d. newfd: %d\n", fd, newfd);

  off = lseek(fd, 0, SEEK_CUR);
  if (off == -1) {
    fprintf(stderr, "main: lseek fd");
    exit(EXIT_FAILURE);
  }

  newoff = lseek(newfd, 0, SEEK_CUR);
  if (newoff == -1) {
    fprintf(stderr, "main: lseek newfd");
    exit(EXIT_FAILURE);
  }

  printf("off: %ld, newoff: %ld\n", (long) off, (long) newoff);

  flag = fcntl(fd, F_GETFL);
  if (flag == -1) {
    fprintf(stderr, "main: fcntl fd");
    exit(EXIT_FAILURE);
  }

  newflag = fcntl(newfd, F_GETFL);
  if (newoff == -1) {
    fprintf(stderr, "main: fcntl newfd");
    exit(EXIT_FAILURE);
  }

  printf("flag: %d, newflag: %d\n", flag, newflag);

  return 0;
}

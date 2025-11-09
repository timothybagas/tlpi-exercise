#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int tdup(int oldfd, int newfd) {
  if (newfd > 2) {
    newfd = fcntl(oldfd, F_DUPFD, newfd);
  } else  {
    newfd = fcntl(oldfd, F_DUPFD);
  }
  if (newfd == -1) {
    fprintf(stderr, "tdup: fcntl F_DUPFD");
    exit(EXIT_FAILURE);
  }
  return newfd;
}

/**
 * According to Man Page, below function would subject to race condition.
 */
int tdup2(int oldfd, int newfd) {
  if (fcntl(oldfd, F_GETFL) == -1) {
    fprintf(stderr, "tdup: fcntl F_GETFL");
    exit(EXIT_FAILURE);
  }
  if (fcntl(newfd, F_GETFL) != -1) {
    close(newfd); // silent close
  }
  return tdup(oldfd, newfd);
}

int getflag(int fd) {
  int flag;
  flag = fcntl(fd, F_GETFL);
  if (flag == -1) {
    fprintf(stderr, "getflag: fcntl F_GETFL");
    exit(EXIT_FAILURE);
  }
  return flag;
}

int main(int argc, char **argv) {
  int fd, newfd, newfd2;
  int flag, newflag, newflag2;

  fd = open("test", O_RDWR | O_CREAT, S_IRWXU);
  if (newfd == -1) {
    fprintf(stderr, "main: open");
    exit(EXIT_FAILURE);
  }

  newfd = tdup(fd, 0);
  printf("fd: %d, newfd: %d\n", fd, newfd);

  flag = getflag(fd);
  newflag = getflag(newfd);
  printf("fd flag: %d, newfd flag: %d\n", flag, newflag);

  newfd2 = tdup2(fd, 4);
  printf("fd: %d, newfd2: %d\n", fd, newfd2);

  return 0;
}

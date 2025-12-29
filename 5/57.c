#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

struct iovec {
  void *iov_base;
  size_t iov_len;
};

ssize_t	readv(int fd, const struct iovec *iov, int iovcnt) {
  ssize_t res;
  int rd;

  if (iovcnt <= 0 || iovcnt > (int) sysconf(_SC_UIO_MAXIOV)) {
    return EINVAL;
  }
  res = 0;

  while (iovcnt--) {
    if (iov) {
      rd = read(fd, iov->iov_base, iov->iov_len);
      if (rd == -1) {
	return -1;
      }
      res += rd;
    }
    iov++;
  }
  return res;
}

ssize_t writev(int fd, struct iovec *iov, int iovcnt) {
  // TODO: writev
  return 0;
}

int main(int argc, char **argv) {
  int fd;
  char buf0[20];
  char buf1[30];
  int iovcnt;
  struct iovec iov[2];

  iov[0].iov_base = buf0;
  iov[0].iov_len = sizeof(buf0);
  iov[1].iov_base = buf1;
  iov[1].iov_len = sizeof(buf1);

  fd = open("lorem.txt", O_RDONLY);
  if (fd == -1) {
    return -1;
  }
  
  iovcnt = sizeof(iov) / sizeof(struct iovec);
  if ((int) readv(fd, iov, iovcnt) == -1) {
    return -1;
  }

  printf("%s%s\n", buf0, buf1);
  
  return 0;
}

#include <fcntl.h>
#include <unistd.h>

/**
 * Output: Giddayworld
 *
 * Explanation: dup shares the same file offset, thus when changing fd2's
 * offset, fd1's offset also affected.
 */
int main(int argc, char **argv) {
  char *file = "test56";
  int fd1,fd2, fd3;
  fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  fd2 = dup(fd1);
  fd3 = open(file, O_RDWR);
  write(fd1, "Hello,", 6);
  write(fd2, "world", 6);
  lseek(fd2, 0, SEEK_SET);
  write(fd1, "HELLO,", 6);
  write(fd3, "Gidday", 6);
  return 0;
}

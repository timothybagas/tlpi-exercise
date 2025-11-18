#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cred.h"

#define BUFSIZE 100000

void exit_failure(const char *msg) {
  fprintf(stderr, msg);
  exit(EXIT_FAILURE);
}

char *getpwlist() {
  int fd, rb;
  char buf[BUFSIZE];
  char *p, *it;

  fd = open("/etc/passwd", O_RDONLY);
  if (fd == -1) {
    exit_failure("open");
  }

  rb = read(fd, buf, BUFSIZE);
  if (rb == -1) {
    exit_failure("read");
  }

  for (it = buf; it != NULL && *it != '\0'; it++) {
    p = it;
    while (*p != '\n' && *p != '\0') p++;
    // TODO: How map a string to mpasswd struct?  
  }
}

mpasswd *mgetpwent(void) {
  int fd, rb;
  char buf[BUFSIZE];
  char *p, *it;

  fd = open("/etc/passwd", O_RDONLY);
  if (fd == -1) {
    exit_failure("open");
  }

  rb = read(fd, buf, BUFSIZE);
  if (rb == -1) {
    exit_failure("read");
  }

  for (it = buf; it != NULL && *it != '\0'; it++) {
    p = it;
    while (*p != '\n' && *p != '\0') p++;

    
  }

  return NULL;
}

void msetpwent(void) {}

void mendpwent(void) {}

mpasswd *mgetpwnam(const char *name)  {
  return NULL;
}

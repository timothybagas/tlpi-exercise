#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1000

int main() {
  char *name;
  name = (char *) malloc(BUFSIZE);

  if (!gethostname(name, BUFSIZE)) {
    printf("hostname: %s\n", name);
  } else {
    fprintf(stderr, "failed to get hostname\n");
  }
  return 0;
}

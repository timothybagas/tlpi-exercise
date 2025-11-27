#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>

#include "passwd.h"

/*
 * Execute command: ./<bin-name> name
 */
int main(int argc, char **argv) {
  char *name;
  struct passwd *mpwent, *pwent;

  if (argc <= 1) {
    return -1;
  }

  name = argv[1];
  mpwent = mgetpwnam(name);
  pwent = getpwnam(name);

  if (mpwent && pwent) {
    printf("%ld %ld\n", (long) mpwent->pw_uid, (long) pwent->pw_uid);
  } else {
    printf("User not found!\n");
  }
  return 0;
}

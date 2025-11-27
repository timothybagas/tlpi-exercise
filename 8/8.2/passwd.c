#include <pwd.h>
#include <string.h>
#include <sys/types.h>

#include "passwd.h"

#define BUFSIZE 100000

struct passwd *mgetpwnam(const char *name) {
  static struct passwd *res;
  struct passwd *ent;

  while (ent = getpwent()) {
    if (!strcmp(ent->pw_name, name)) {
      res = ent;
      break;
    }
  }

  endpwent();
  return res;
}

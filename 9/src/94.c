#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

void printresuid(char *s, uid_t ruid, uid_t euid, uid_t suid) {
  printf("%s: r: %ld, e: %ld, s: %ld\n", s, (long) ruid, (long) euid, (long) suid);
}

int main() {
  uid_t ruid, euid, suid;

  // exercise 9.4.a
  getresuid(&ruid, &euid, &suid);
  printresuid("before suspended", ruid, euid, suid);

  setreuid(-1, getuid()); // set effective UID to real UID
  getresuid(&ruid, &euid, &suid);
  printresuid("after suspended", ruid, euid, suid);

  if (setresuid(-1, suid, -1) == -1) { // set effective UID to saved SUID
    return -1;
  }
  getresuid(&ruid, &euid, &suid);
  printresuid("after resumed", ruid, euid, suid);
  
  // IMPORTANT! for some reason:
  // - setuid and seteuid cannot restore the effective UID from saved SUID
  // - setreuid and setresuid can restore the effective UID from saved SUID

  return 0;
}

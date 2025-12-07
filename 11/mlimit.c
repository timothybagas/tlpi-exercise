#include <limits.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  long lim;

  // Runtime Invariant Values
  //
  // Limit whose value, if defined in <limits.h>, is fixed for the implementation.
  // However, the value may be intermediate, and hence omitted from <limits.h>.
  lim = sysconf(_SC_MQ_PRIO_MAX);
  printf("_SC_MQ_PRIO_MAX: %ld\n", lim);

  // Pathname Variable
  //
  // Limits that relate to pathnames (files, dirs, terminals, etc).
  lim = pathconf(".", _PC_NAME_MAX);
  printf("_PC_NAME_MAX: %ld\n", lim);

  lim = pathconf(".", _PC_LINK_MAX);
  printf("_PC_LINK_MAX: %ld\n", lim);

  // Runtime Increasable Values
  //
  // Has a fixed min value but a specific system may increase this limit at runtime.
  lim = pathconf(".", _SC_NGROUPS_MAX);
  printf("_SC_NGROUPS_MAX: %ld\n", lim);

  // System Options
  //
  // Value -1 means that the option is not supported.
  // Value 0 means that the option may be supported.
  // Value greater than 0 means that the option is supported.
  printf("> Are the following options supported?\n");
  printf("_SC_ASYNCHRONOUS_IO: %d\n", _SC_ASYNCHRONOUS_IO);
  printf("_PC_CHOWN_RESTRICTED: %d\n", _PC_CHOWN_RESTRICTED);
  printf("_SC_JOB_CONTROL: %d\n", _SC_JOB_CONTROL);
  printf("_SC_MESSAGE_PASSING: %d\n", _SC_MESSAGE_PASSING);
  printf("_SC_SEMAPHORES: %d\n", _SC_SEMAPHORES);
  printf("_SC_THREADS: %d\n", _SC_THREADS);

  return 0;
}

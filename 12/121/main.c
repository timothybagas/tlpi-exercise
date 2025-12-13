#include <dirent.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#define BUFSIZE 1024

void logproc(uid_t in_uid, char *dname) {
  static char fulldir[BUFSIZE];
  char buffer[BUFSIZE];
  FILE *fp;

  pid_t pid;
  char cmd[BUFSIZE];
  uid_t uid;

  sprintf(fulldir, "/proc/%s/status", dname);

  fp = fopen(fulldir, "r");
  if (fp == NULL) return;

  while (fgets(buffer, BUFSIZE, fp)) {
    if (strncmp(buffer, "Name:", 5) == 0) {
      sscanf(buffer + 5, "%s", cmd);
    } else if (strncmp(buffer, "Uid:", 4) == 0) {
      sscanf(buffer + 4, "%d", &uid);
    } else if (strncmp(buffer, "Pid:", 4) == 0) {
      sscanf(buffer + 4, "%d", &pid);
    }
  }

  if (in_uid == uid) {
    printf("Program Name: %s | PID: %ld\n", cmd, (long) pid);
  }
}

int isnumber(char *s) {
  if (*s == '\0') return 0;
  if (*s == ' ') return 0;
  while (s) {
    if (*s == '\0') break;
    if (!(*s >= '0' && *s <= '9')) return 0;
    s++;
  }
  return 1;
}

int main(int argc, char **argv) {
  char *name;
  struct passwd *user;

  char *dname;
  DIR *dir;
  struct dirent *dirs;

  if (argc < 2) {
    fprintf(stderr, "%s must be supplied with 1 argument\n", argv[0]);
    return -1;
  }

  name = argv[1];
  user = getpwnam(name);
  printf("listing all spawned processes by user: %s\n", user->pw_name);

  dir = opendir("/proc");
  dirs = readdir(dir);

  while (dirs != NULL) {
    dname = dirs->d_name;

    if (!isnumber(dname)) {
      dirs = readdir(dir);
      continue;
    }

    logproc(user->pw_uid, dname);
    dirs = readdir(dir);
  }

  printf("All processes by user: %s were listed\n", user->pw_name);

  return 0;
}

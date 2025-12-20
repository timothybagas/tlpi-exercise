#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define PROC_MAX 10000
#define CHILD_MAX 10
#define BUFSIZE 1024

int childcnt[PROC_MAX] = {0}; // child count of a PID
int childs[PROC_MAX][CHILD_MAX] = {0}; // child PIDs
char *cmd[PROC_MAX]; // cmd of a PID

int printed[PROC_MAX] = {0}; // flag to indicate the process was printed

/**
 * Prints the proc tree recursively.
 */
void printtree(int pid, int level) {
  if (cmd[pid] == NULL) return;
  if (printed[pid]) return;

  char *buffer;
  buffer = (char *) malloc(BUFSIZE);
  char *b = buffer;

  for (int i = 1; i < level; i++) {
    *b = ' ';
    b++;
  }
  *b = '-';
  b++;

  *b = ' ';
  b++;
  
  strcpy(b, cmd[pid]);

  printf("%s\n", buffer);
  printed[pid] = 1;

  for (int i = 0; i < childcnt[pid]; i++) {
    printtree(childs[pid][i], level + 1);
  }
}

/**
 * Collects the childcnt, childs, and cmd.
 */
void getproc(uid_t in_uid, char *pidnam) {
  static char fulldir[BUFSIZE];
  char buffer[BUFSIZE];
  FILE *fp;

  char *cmdb;
  uid_t uid;
  pid_t pid;
  pid_t ppid;

  cmdb = (char *) malloc(BUFSIZE);
  sprintf(fulldir, "/proc/%s/status", pidnam);

  fp = fopen(fulldir, "r");
  if (fp == NULL) return;

  while (fgets(buffer, BUFSIZE, fp)) {
    if (strncmp(buffer, "Name:", 5) == 0) {
      sscanf(buffer + 5, "%s", cmdb);
    } else if (strncmp(buffer, "Uid:", 4) == 0) {
      sscanf(buffer + 4, "%d", &uid);
    } else if (strncmp(buffer, "Pid:", 4) == 0) {
      sscanf(buffer + 4, "%d", &pid);
    } else if (strncmp(buffer, "PPid:", 5) == 0) {
      sscanf(buffer + 5, "%d", &ppid);
    }
  }

  if (in_uid != uid) return;
  if (pid > PROC_MAX || ppid > PROC_MAX) return;

  childcnt[ppid]++;
  if (childcnt[ppid] >= CHILD_MAX) return;

  childs[ppid][childcnt[ppid] - 1] = pid;
  cmd[pid] = cmdb;
  // printf("pid: %ld, ppid: %ld, cmd: %s\n", (long) pid, (long) ppid, cmd[pid]);
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

  char *pidnam;
  DIR *dir;
  struct dirent *procs;

  int pid;

  if (argc < 2) {
    fprintf(stderr, "[main] %s must be supplied with 1 argument\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  name = argv[1];
  user = getpwnam(name);

  if (user == NULL) {
    fprintf(stderr, "[main] user is NULL\n");
    exit(EXIT_FAILURE);
  }

  dir = opendir("/proc");
  procs = readdir(dir);

  while (procs != NULL) {
    pidnam = procs->d_name;

    if (!isnumber(pidnam)) {
      procs = readdir(dir);
      continue;
    }

    getproc(user->pw_uid, pidnam);
    procs = readdir(dir);
  }

  for (int i = 0; i < PROC_MAX; i++)
    printtree(i, 1);

  return 0;
}

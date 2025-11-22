struct mpasswd_s {
  char   *pw_name;       /* username */
  char   *pw_passwd;     /* user password */
  long    pw_uid;        /* user ID */
  long    pw_gid;        /* group ID */
  char   *pw_gecos;      /* user information */
  char   *pw_dir;        /* home directory */
  char   *pw_shell;      /* shell program */
};
typedef struct mpasswd_s mpasswd;

mpasswd *mgetpwent(void);
void msetpwent(void);
void mendpwent(void);
mpasswd *mgetpwnam(const char *name);

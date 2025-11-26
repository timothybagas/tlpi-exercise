# Chapter 9

## 9.1
Assume in each of the following cases that  the  initial  set  of  process user  IDs  is `real=1000  effective=0  saved=0  file-system=0`.  What  would  be the  state  of  the  user  IDsafter the following calls?

### a) `setuid(2000)`
**Output:** `real=2000  effective=2000  saved=2000  file-system=0`

**Reason:** Because `effective=0` (privilege).

### b) `setreuid(-1, 2000)`
**Output:** `real=1000  effective=2000  saved=2000  file-system=2000`

**Reason:**
Because `effective=0` (privilege), saved changed becuase `new effective != prev effective`, file-system follows the effective ID. 

### c) `seteuid(2000)`
**Output:** `real=1000  effective=2000  saved=0  file-system=2000`

**Reason:**
Because `effective=0` (privilege), file-system follows the effective ID. 

### d) `setfsuid(2000)`
**Output:** `real=1000  effective=0  saved=0  file-system=2000`

**Reason:**
Because `effective=0` (privilege). Otherwise update will be ignored. 

### e) `setresuid(-1, 2000, 3000)`
**Output:** `real=1000  effective=2000  saved=3000  file-system=2000`

**Reason:**
Because `effective=0` (privilege) it could change the values arbitrarily.

## 9.2
Is a process with the following user IDs privileged? Explain your answer.

`real=0 effective=1000 saved=1000 file-system=1000`

**Answer:** No, regardless of `real=0`, the effective ID does not have privilege access.

## 9.3
Implemented in `93.c`.

## 9.4
```
uid_t euid = geteuid();
// setuid and seteuid cannot restore effective UID from saved SUID

// 9.4.a) Suspend then resume
setreuid(-1, getuid()); // Suspend. Alternative: setresuid(-1, getuid(), -1);
setreuid(-1, euid); // Resume. Alternative: setresuid(-1, euid, -1);

// 9.4.b) Drop permanently
setreuid(geteuid(), getuid()); // Drop. Alternative: setresuid(getuid(), getuid(), getuid());
```

## 9.5
Same as `9.4` since below is the output of program `9.4`:
```
before suspended: r: 1000, e: 0, s: 0
after suspended: r: 1000, e: 1000, s: 0
after resumed: r: 1000, e: 0, s: 0
```
**NOTE:** Need to `chown u+s <output-binary>` to get above output.

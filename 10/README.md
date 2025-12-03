# Chapter 10

We may interested in 2 kinds of time:

- _Real time_: Measured from some standard point (calendar time) or from some fixed point.
- _Process time_: Amount of CPU time used by a process.

## 10.1 Calendar Time

Regardless  of  geographic  location,  UNIX  systems  represent  time
internally  as  ameasure  of  seconds  since  the  Epoch;  that  is,  since
midnight  on  the  morning  of1 January  1970,  Universal  Coordinated  Time.

The `gettimeofday()` system call returns the calendar time in the buffer pointed
to by `tv`. The `tz` argument to `gettimeofday()` is  a  historical  artifac nd
should always be specified as NULL.

```c
#include <sys/time.h>

int gettimeofday(struct timeval *tv, struct timezone *tz);
```

The `time()` system call returns the number of seconds since the Epoch.

```c
#include <time.h>

time_t time(time_t *timep);
```

### 10.2.1 Converting _time_t_ to Printable Form

The `ctime()` function  provides  a  simple  method  of  converting  a  `time_t`
value  intoprintable form.

```c
#include <time.h>

char *ctime(const time_t *timep);
```

`ctime()` returns a 26-byte string containingthe date and time in a standard
format.

### 10.2.2 Converting Between _time_t_ and Broken-Down Time

The `gmtime()` and `localtime()` functions convert a `time_t` value into a so-called
broken-down time.

```c
#include <time.h>

struct tm *gmtime(const time_t *timep);
struct tm *localtime(const time_t *timep);
```

The `gmtime()`  function  converts  a  calendar  time  into  a  broken-down  time
corresponding to UTC. (The letters gm derive from Greenwich Mean Time.) By
contrast, `localtime()` takes into account timezone and DST settings to return
a broken-downtime corresponding to the system’s local time.

The `mktime()` function translates a broken-down time, expressed as local
time, into a `time_t` value, which is returned as the function result. 

```c
#include <time.h>

time_t mktime(struct tm *timeptr);
```

`mktime()`  doesn’t  require  the  other  fields  of  the  `tm`  structure  to
be restricted to the ranges. `mktime()` adjusts that field’s value so that it is
in range and makes suitable adjustments to the other fields.

For example, if the input `tm_sec` field were 123, then on return, the value of
this field would be 3, and the value of the `tm_min` field would have 2 added to
whatever value it previously had. (And if that addition caused `tm_min` to
overflow, then the `tm_min` value would be adjusted and the `tm_hour` field would be
incremented, and so on.)

### 10.2.3 Converting Between Broken-Down Time and Printable Form

Given  a  pointer  to  a  broken-down  time  structure  in  the  argument  `tm`,
`asctime()` returns  a  pointer  to  a  statically  allocated  string  containing
the  time  in  the  sameform as `ctime()`.

```c
#include <time.h>

char *asctime(const struct tm *timeptr);
```

By contrast with `ctime()`, local timezone settings have no effect on `asctime()`,
since itis  converting  a  broken-down  time  that  is  typically  either
already  localized  via `localtime()` or in UTC as returned by `gmtime()`.

The `strftime()`  function  provides  us  with  more  precise  control  when
converting  a broken-down  time  into  printable  form.  Given  a  broken-down
time  pointed  to  by `timeptr`, `strftime()`  places  a  corresponding
null-terminated,  date-plus-time  string  in the buffer pointed to by `outstr`.

```c
#include <time.h>

size_t strftime(char *outstr, size_t maxsize, const char *format,
                const struct tm *timeptr);
```

The `strptime()` function uses the specification given in format to parse the
date-plus-time string given in `str`, and places the converted broken-down time
in the structure pointed to by `timeptr`.

```c
#define _XOPEN_SOURCE
#include <time.h>

char *strptime(const char *str, const char *format, struct tm *timeptr);
```

The glibc  implementation  of  `strptime()`  doesn’t  modify  those  fields  of
the  tmstructure  that  are  not  initialized  by  specifiers  in  `format`.

## 10.3 Timezones

These files reside in the directory `/usr/share/zoneinfo`. The  local  time
for  the  system  is  defined  by  the  timezone  file  `/etc/localtime`, which is
often linked to one of the files in `/usr/share/zoneinfo`.

## 10.4 Locales

Locale  information  is  maintained  in  a  directory  hierarchy  under
`/usr/share/locale` (or `/usr/lib/locale` in some distributions).

## 10.5 Updating the System Clock

Two  interfaces  that  update  the  system  clock:  `settimeofday()`
and `adjtime()`.  These  interfaces  are  rarely  used  by  application  programs
(since  the  sys-tem time is usually maintained by tools such as the _Network
Time Protocol daemon_), and they require that the caller be privileged (`CAP_SYS_TIME`).

```c
#define _BSD_SOURCE
#include <sys/time.h>

int settimeofday(const struct timeval *tv, const struct timezone *tz);
```

The `settimeofday()` system call sets  the  system’s  calendar  time  to  the
number  of  seconds and microseconds specified in the timeval structure
pointed to by `tv`.

Abrupt changes in the system time have  deleterious  effects  on  applications.
It is usually preferable to use the `adjtime()` library function, which causes the
system clock to gradually adjust to the desired value.

```c
#define _BSD_SOURCE
#include <sys/time.h>

int adjtime(struct timeval *delta, struct timeval *olddelta);
```

The `delta` argument points to a timeval structure that specifies the number of
seconds and microseconds by which to change the time.

It  may  be  that  an  incomplete  clock  adjustment  was  in  progress  at
the  time  of  the `adjtime()` call. In this case, the amount of remaining,
unadjusted time is returned in the `timeval` structure pointed to by `olddelta`.

## 10.6 The Software Clock (Jiffies)

The accuracy of various time-related system calls described in this book is
limited to  the  resolution  of  the  system  _software  clock_,  which  measures
time  in  units  called `jiffies`. The size of a jiffy is defined by the constant
HZ within the kernel source code.This is the unit in which the kernel allocates
the CPU to processes under the round-robin time-sharing scheduling algorithm.

## 10.7 Process Time

The kernel separates CPU time into:

- User CPU time is the amount of time spent executing in user mode.
- System CPU time is amount of time spent executing in kernel mode.

The `times()` system call retrieves process time information.

```c
#include <sys/times.h>

clock_t times(struct tms *buf);
```

The reliable  way  to  measure  the  passage  of  elapsed  time  is  touse
`gettimeofday()`.

The `clock()`  function  provides  a  simpler  interface  for  retrieving  the
process time. It returns a single value that measures the total (i.e., user plus
system) CPU time used by the calling process.

```c
#nclude <time.h>

clock_t clock(void);
```

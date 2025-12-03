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

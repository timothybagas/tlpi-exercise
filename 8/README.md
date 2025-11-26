# Chapter 8

## 8.1
> When  we  execute  the  following  code,  we  find  that  it  displays  the
same  numbertwice, even though the two users have different IDs in the password
file. Why is this?
```
printf("%ld %ld\n", (long) (getpwnam("avr")->pw_uid),
                    (long) (getpwnam("tsr")->pw_uid));
```
 
**Answer:**
The manual page of `getpwnam` states that: "The return value may point to
a <ins>**static area**</ins>, and may be overwritten by subsequent calls to
`getpwent(3)`, `getpwnam()`, or `ge    tpwuid()`"
Meaning both calls point to the same memory address and thus point to the same
value.

## 8.2
> Implement `getpwnam()` using `setpwent()`, `getpwent()`, and `endpwent()`.

Implemented within the `8.2`.

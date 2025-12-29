# Chapter 5

- `fctnl`: retrieve (`F_GETFL`) or modify (`F_SETFL`) file status flags
    - AND with `O_ACCMODE` to get access mode
- Multiple descriptors could refer to the same file
- Three data structures maintained by the kernel:
    - per-process file descriptor table
    - system wide file description table
    - i-node file system table
- Use `dup`, `dup2`, `dup3`, or `fcntl` with `FDUPFD` to duplicate file descriptor
- `pread` and `pwrite` to specify file offset of a file descriptor without changing the original offset
- `readv` and `writev` for scatter-gather I/O (bulk buffers)
- `preadv` and `pwritev` combine specified offset and scatter-gather I/O
- `truncate` and `ftruncate` to update file size (longer got truncated, shorter got appended with hole)
- `open` with `O_NONBLOCK`:
    - If a file can't be opened immediately, `open` will return an error instead of blocking
    - After a successfull `open`, subsequent I/O operations are nonblocking
- Use `_FILE_OFFSET_BITS` macro for large files (or `_LARGEFILE64_SOURCE` as an alternative - LFS transitional API)
- `/dev/fd` is a special virtual directory which contain links to open file descriptors
- Use `mkstemp` to create temporary files (with 6 XXXXXX last characters) or `tmpfile`

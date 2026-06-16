# Kernel Hacking xv6 (risc)

This fork of xv6 works through the projects from OSTEP. 

[Project Page](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master)

# 1: Adding a Syscall 

The first assignment was to add a syscall to xv6. The syscall simply returns how many times a process has called the read() syscall. 

To do this, we register the syscall number, add a field for read_count in the proc structure, and 

- in sys_read(), before returning on success, increment the read_count field in the process
- sys_readcount() simply returns the process's current count. 

Then, a test in userspace was added (and the syscall registered), and can be checked with 

```bash
./test-xv6.py countread
```

# 2: Implementing a Scheduler 

(in progress)



set env LD_PRELOAD=.

gdb /bin/ls

(gdb) set exec-wrapper env LD_PRELOAD=./libmalloc.so
(gdb) b malloc.c:malloc








(gdb) set env LD_LIBRARY_PATH=.
(gdb) b main
Breakpoint 1 at 0x4007b4: file src/unit.c, line 129.
(gdb) r
Starting program: /afs/cri.epita.net/user/n/ni/nicolas.pelletier/u/malloc/unit
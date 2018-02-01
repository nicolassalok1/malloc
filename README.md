set env LD_PRELOAD=.

gdb /bin/ls

(gdb) set exec-wrapper env LD_PRELOAD=./libmalloc.so
(gdb) b malloc.c:malloc








(gdb) set env LD_LIBRARY_PATH=.
(gdb) ...
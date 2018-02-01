set env LD_PRELOAD=./libmalloc.so

gdb -q /bin/ls
(gdb) set exec-wrapper env 'LD_PRELOAD=./libmalloc.so'
(gdb) b malloc.c:malloc
(gdb) y
(gdb) set env LD_LIBRARY_PATH=.

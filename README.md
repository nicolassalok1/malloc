(gdb) set exec-wrapper env LD_PRELOAD=./libmalloc.so
(gdb) b malloc.c:malloc
Aucune table de symboles n'est chargÃ©e. Utiliser la commande Â«Â fileÂ Â»
Make breakpoint pending on future shared library load? (y or [n]) y
Breakpoint 1 (malloc.c:malloc) pending.
(gdb) start
Function "main" not defined.
Make breakpoint pending on future shared library load? (y or [n]) y
Temporary breakpoint 2 (main) pending.
Starting program: /bin/ls
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Breakpoint 1, malloc (size=552) at src/malloc.c:10
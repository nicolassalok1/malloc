#!/bin/bash
make
set env LD_LIBRARY_PATH=.
set env LD_PRELOAD=./libmalloc.so
gdb /bin/ls -x gdb_command 

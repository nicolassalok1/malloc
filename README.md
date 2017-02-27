set env LD_LIBRARY_PATH =.

set exec -wrapper env 'LD_PRELOAD =./ libmalloc.so '

break malloc.c:malloc
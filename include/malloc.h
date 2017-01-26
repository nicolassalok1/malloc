#ifndef MALLOC_H
#define MALLOC_H
#define _BSD_SOURCE
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>

#define TAILLE_BLOCK_MIN  512
#define TAILLE_PAGE sysconf(_SC_PAGESIZE)

struct mymeta
{
  size_t block_size;
  void *page_address;
  char is_free[4096 / TAILLE_BLOCK_MIN];
  struct mymeta *next;
};

struct mymeta *tab_plus_plus(void *input);
size_t get_offset(void);
struct mymeta *get_metatab (void);
void free (void* input);
void *malloc(size_t size);
void *alloc(struct mymeta *tmp, size_t num, int flag);
void *alloc_calloc(struct mymeta *tmp, size_t num);
size_t tabsize(void);
struct mymeta *find_metadata (void *input, struct mymeta *tab);
int is_registered (void *input, struct mymeta *tab);
void new_page(struct mymeta *tmp, size_t num);
void build_metatab (void);
int is_it_free(struct mymeta tmp,  size_t num);
struct mymeta *build_metacase(size_t size);
void *realloc (void* input, size_t size);
void *gros_malloc(size_t size, struct mymeta *tab, size_t num, int flag);
size_t puissance2(size_t i);
char *concat(char *s1, char *s2);

#endif //MALLOC_H

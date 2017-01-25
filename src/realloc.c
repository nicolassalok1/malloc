#include "malloc.h"
#define LIB_VISIBLE __attribute__((__visibility__("default")))


LIB_VISIBLE
void *realloc (void* input, size_t size)
{
  struct mymeta *tab = NULL;
  tab = get_metatab();

  if (is_registered(input, tab))
  {
    struct mymeta *res;
    res = find_metadata(input, tab);
    if (size <= res->block_size)
      return input;
    free(input);
    return malloc(size);
  }
  return NULL;
}
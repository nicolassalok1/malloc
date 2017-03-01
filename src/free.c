
#include "malloc.h"
#define LIB_VISIBLE __attribute__((__visibility__("default")))




LIB_VISIBLE
void free (void* input)
{
  struct mymeta *tab = NULL;
  tab = get_metatab();
  
  if (is_registered(input, tab))
  {
    //size_t i;
    struct mymeta *res;
    res = find_metadata(input, tab);
    char *buffer = res->page_address;
    //char *tab_is_free = res->is_free;

    for (size_t k = 0; k < TAILLE_PAGE/res->block_size; k++)
    {
      if (input == buffer)
      {
        res->is_free[k] = '1';
        break;
      }
      buffer += res->block_size;
    }
  }
  else
    printf("ya ain't no rights to free dat bitch");
    
}

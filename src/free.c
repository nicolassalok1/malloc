
#include "malloc.h"
#define LIB_VISIBLE __attribute__((__visibility__("default")))




LIB_VISIBLE
void free (void* input)
{
  struct mymeta *tab = NULL;
  tab = get_metatab();
  
  if (is_registered(input, tab))
  {
    int i;
    struct mymeta *res;
    res = find_metadata(input, tab);
    char *tmp = res->page_address;
    char *tab_is_free = res->is_free;

    while ((tab_is_free[i]) && (tmp != input))
    {
      tmp += res->block_size;
      i++;
    }

    if  (tab_is_free[i])
    {
      //if (res.block_size <= TAILLE_PAGE)
        tab_is_free[i] = '1';
      /*else
      {
        //FAIRE QQCHOSE SI DES GROSSES CASES SONT FREE
      }*/
    }
    else
      printf("ya ain't no rights to free dat bitch");
    
  }
}

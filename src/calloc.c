#include "malloc.h"
#define LIB_VISIBLE __attribute__((__visibility__("default")))




LIB_VISIBLE
void *calloc (size_t num, size_t size)
{
  struct mymeta *tab;
  tab = NULL;
  tab = get_metatab();

  long teub = size * num;
  
  if (teub > TAILLE_PAGE)
    return gros_malloc(size, tab, num, 1);

  struct mymeta *tmp;
  struct mymeta *pre_tmp;
  size_t k = tabsize();

  while ((k > 0) && (size > tab[k].block_size))
    k--;

  tmp = &tab[k];

  if ((tmp->page_address) && (is_it_free(*tmp,num)))
    return alloc_calloc(tmp, num);

  while ((tmp->next) && (tmp->page_address) && (is_it_free(*tmp, num) == -1))
  {
    pre_tmp = tmp;
    tmp = tmp->next;
  }

  if ((is_it_free(*tmp, num)) && (tmp->page_address))
    return alloc_calloc(tmp, num);
  else if (!(tmp->page_address))
  {
    new_page(tmp, num);
    return alloc_calloc(tmp, num);
  }

  build_metacase(pre_tmp->block_size);
  pre_tmp->next = tmp;
  new_page(tmp, num);

  return alloc_calloc(tmp, num);
}










void *alloc_calloc(struct mymeta *tmp, size_t num)
{
  char *res = tmp->page_address;
  char *tab = tmp->is_free;
  int index = is_it_free(*tmp, num);

  res += index * tmp->block_size;

  char *teub = res;

  for (size_t k = 0; k < (tmp->block_size * num) / 8; k++)
  {
    *teub = 0;
    teub++;
  }
    
  for (size_t j = 0; j < num; j++)
  {
    tab[j] = '0';
  }

  return res;
}

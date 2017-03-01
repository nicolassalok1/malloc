#include "malloc.h"
#define LIB_VISIBLE __attribute__((__visibility__("default")))




LIB_VISIBLE
void *malloc(size_t size)
{
	long long_teub = size;

  size = size;

  struct mymeta *tab;
  tab = NULL;

  tab = get_metatab();
  
  tab = tab;

  if (long_teub > TAILLE_PAGE)
    return gros_malloc(size, tab, 1, 0);

  size_t k;
  k = tabsize() - 1;

  while ((k > 0) && (size > tab[k].block_size))
  {
    k--;
  }

  
  if ((tab[k].page_address) && (is_it_free(tab[k], 1) != -1))
    return alloc(&tab[k], 1, 0);

  struct mymeta *tmp = &tab[k];
  struct mymeta *pre_tmp = NULL;

  while ((tmp) && (tmp->page_address)/* && (tmp->next)*/ && (is_it_free(*tmp, 1) == -1))
  {
    pre_tmp = tmp;
    tmp = tmp->next;
  }

  if ((tmp) && (tmp->page_address) && (is_it_free(*tmp, 1) != -1))
    return alloc(tmp, 1, 0);


  else if ((tmp) && (!(tmp->page_address)))
  {
    new_page(tmp, 1);
    return alloc(tmp, 1, 0);
  }

  pre_tmp->next = build_metacase(pre_tmp->block_size);

  new_page(pre_tmp->next, 1);

  return alloc(pre_tmp->next, 1, 0);

}














void *gros_malloc(size_t size, struct mymeta *tab, size_t num, int flag)
{
  size_t taille_totale = size * num;
  size_t res = taille_totale + TAILLE_PAGE;
  res -= taille_totale % TAILLE_PAGE;

  if (!(tab->next))
  {
    struct mymeta *tmp;
    tmp = build_metacase(res);
    tab->next = tmp;
    new_page(tmp, num);
    return alloc(tmp, num, flag);
  }
  
  struct mymeta *pre_tmp = tab;
  struct mymeta *tmp = pre_tmp->next;

  
  while (tmp->next)
  {
    pre_tmp = tmp;
    tmp = tmp->next;
  }

  tmp = build_metacase(res);
  pre_tmp->next = tmp;
  new_page(tmp, num);

  return alloc(tmp, num, flag);
  
}















void *alloc(struct mymeta *tmp, size_t num, int flag)
{

  if (!flag)
  {
    char *offset = tmp->page_address;
    char *tab = tmp->is_free;
    int i = is_it_free(*tmp, num);

    for (int j = 0; j < i; j++)
    {
      offset += tmp->block_size;
    }
    tab[i] = '0';
    void *res = offset;
    return res;
  }
  else
    return alloc_calloc(tmp, num);

}


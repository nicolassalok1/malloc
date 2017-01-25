#include "malloc.h"

size_t tabsize(void)//struct mymeta *tab)
{
  size_t n = TAILLE_PAGE;
  size_t res = 0;
  
  while (n >= TAILLE_BLOCK_MIN)
  {
    res++;
    n /= 2;
  }
  return res;
}

int is_it_free(struct mymeta tmp, size_t num)
{
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;
  char *tab = tmp.is_free;

  while (tab[i])
  {
    if (tab[i] == '1')
    {
      j = i;
      k++;
      while ((k <= num) && (tab[i] == '1'))
      {
        if (k == num)
          return j;
        else
          i++;
        k++;
      }
    }
    k = 0;
    i++;
  }
  return -1;
}

size_t puissance2(size_t i)
{ 
  int res = 1;
  while (i)
  {
    res *= 2;
    i--;
  }
  return res;
}

char *concat(char *s1, char *s2)
{
  size_t i = 0;
  size_t j = 0;

  while (s1[i])
    i++;

  while (s2[j])
    j++;

  s1 =realloc(s1, i + j);// ou i + j

  j = i;

  while(s2[j])
  {
    s1[i] = s2[j];
    j++;
  }

  s1[j] = '\0';

  return s1;
}

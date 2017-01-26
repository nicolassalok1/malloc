#include "malloc.h"

struct mymeta *tableau = NULL;

int is_registered (void *input, struct mymeta *tab)
{
  size_t i;
  int flag = 0;
  char *buffer = NULL;
  long k = 0;
  char *char_input = input;
  
  i = tabsize();
  
  struct mymeta *tmp;
  
  while (i > 0)
  {
    tmp = &tab[i];
    buffer = tmp->page_address;
    while ((tmp->next) && (char_input >= buffer))
    {

		  for (; k < TAILLE_PAGE; k++)
		  {
				buffer++;
		  }
		 	if (char_input <= buffer)
		  {
		  	flag = 1;
		    break;
		  }
		  tmp = tmp->next;
  	}
  	i++;
  }
  
  if (!flag)
    return 0;

  k = 0;
  char *teub = tmp->page_address;

  while ((k < TAILLE_PAGE) && (teub != input))
  {
    teub += tmp->block_size;
  }
  if (k < TAILLE_PAGE)
    return 1;
    
  return 0;
}



struct mymeta *get_metatab (void)
{

  if (!tableau)
    build_metatab();

  return tableau;
}

struct mymeta *find_metadata (void *input, struct mymeta *tab)
{
  size_t i;
  i = tabsize();
  int flag = 0;
  long k = 0;
  char *buffer = NULL;
  struct mymeta *tmp;
  char *char_input = input;
  
  while (i > 0)
  {
    tmp = &tab[i];
    
    while ((tmp->next) && (char_input <= buffer))
    {
    	buffer = tmp->page_address;
		  for (; k < TAILLE_PAGE; k++)
		  {
				buffer++;
		  }
		 	if (char_input <= buffer)
		  {
		  	flag = 1;
		    break;
		  }
		  tmp = tmp->next;
  	}
  	if (flag)
  		break;
  	i++;
  }
 	return tmp;
}









void new_page(struct mymeta *tmp, size_t num)
{	
  char *tab_is_free = tmp->is_free;
  long taille_totale = tmp->block_size * num;
  
  
  if (taille_totale > TAILLE_PAGE) //GROS MALLOC
  {
    tmp->page_address = mmap(0, taille_totale, PROT_READ|PROT_WRITE,MAP_PRIVATE/*|MAP_ANONYMOUS*/, -1, 0);

    
    char *buffer = tmp->page_address;
    long i = 0;
  
    while (i < TAILLE_PAGE)
    {
      i++;
      buffer = NULL;
      buffer++;
    }
    
    *tab_is_free = '\0';

    for (size_t j = 0; j < num; j++)
    {
      tmp->is_free[j] = '1';
    }

  }
 
  tmp->page_address = mmap(0, 4096, PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
  
  if (!tmp->page_address)
    printf("error");


  /*char *buffer = tmp->page_address;//?????????
  long i = 0;

  while (i < TAILLE_PAGE)
  {
    i++;
    buffer = NULL;
    buffer++;
  }
  */

  munmap(tmp->page_address, 4096);
  
  size_t nb_case = TAILLE_PAGE / tmp->block_size;
  *tab_is_free = '\0';
  for (size_t j = 0; j < nb_case; j++)
  {
      tmp->is_free[j] = '1';
  }

}




void build_metatab (void)
{
  size_t nb_case = 0;
  long taille_page = TAILLE_PAGE;
  long n = taille_page;
  size_t deux_puiss_i = 0;

  //struct mymeta *tmp = NULL;

  while (n >= TAILLE_BLOCK_MIN)
  {
    nb_case++;
    n /= 2;
  } 

  n = taille_page;

  tableau = mmap(0, 4096, PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

  if (!tableau)
    printf("error");

  size_t i = 0;

  for (; i < nb_case; i++)
  {
    deux_puiss_i = puissance2(i);
  	n = taille_page / deux_puiss_i;
    build_metacase(n);
  }

}

struct mymeta *build_metacase(size_t size)
{
  static struct mymeta *my_buffer = NULL;

  if (!my_buffer)
    my_buffer = tableau;


  size_t nb_bit;
  long teub = size;

  my_buffer->block_size = size;
  my_buffer->page_address = NULL;
  my_buffer->next = NULL;


  if (teub < (TAILLE_PAGE / 2))
    nb_bit = TAILLE_PAGE / size;
  else
    nb_bit = 1;

  for (size_t j = 0; j < nb_bit; j++)
  {
    my_buffer->is_free[j] = '0';
  }

  return my_buffer++;//belek au ++
}





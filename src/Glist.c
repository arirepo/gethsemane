#include <stdio.h>
#include <stdlib.h>
#include "Glist.h"



int Glist_init_zero(Glist* lst)
{

  lst->size = 0;
  lst->first = (Gitem *)NULL;
  lst->last =  (Gitem *)NULL;

  return 0;

}


 
int Glist_add(Glist* lst, void *opq)
{

  Gitem *tail = lst->last;

  lst->last = (Gitem *) malloc( sizeof(Gitem) );
  if ( lst->last == NULL ) return 1; /* error code */
  lst->last->opq = opq;

  if ( lst->size == 0 ) /* if the list is currently empty */
    {
      lst->first = lst->last;
      lst->size = 1;
    }
  else
    {
      tail->nxt = lst->last;
      lst->last->prv = tail;
      lst->size++;
    }
  return 0;
}

int Glist_print(char *name, Glist* lst)
{

  Gitem *ptr = (Gitem *) NULL;
  printf(" %s = { size = %d, item(s) = ", name, lst->size);
  for(ptr = lst->first; ptr != NULL; ptr = ptr->nxt)
    printf("%p, ", (void *)ptr->opq);

  printf("}. ");

  return 0;

}

int Glist_clear(Glist *lst)
{
  Gitem *ptr0 = NULL, *ptr1 = NULL;
  if ( lst->size )
    {
      for(ptr0 = lst->first; (ptr1 = ptr0->nxt) != NULL; ptr0 = ptr1)
	{
	  free(ptr0->opq);
	  free(ptr0);
	}
      free(ptr0->opq);
      free(ptr0);
    }

  free(lst);

  return 0;
}

int Glist_delete(Glist *lst, int indx)
{
  int i;
  Gitem *cur = lst->first;

  for ( i = 0; i < indx; i++)
    cur = cur->nxt;

  /* in the middle of the Glist */
  if ( (cur->prv != NULL) && (cur->nxt != NULL) )
    {
      cur->prv->nxt = cur->nxt;
      cur->nxt->prv = cur->prv;
    } 
  /* at the end of the Glist */
  else if ( (cur->prv != NULL) && (cur->nxt == NULL) )
    {
      cur->prv->nxt = NULL;
      lst->last = cur->prv;
    } 
  /* at the beginning of the Glist */
  else if ( (cur->prv == NULL) && (cur->nxt != NULL) )
    {
      cur->nxt->prv = NULL;
      lst->first = cur->nxt;
    }

  free(cur->opq);
  free(cur); 
  lst->size--;

  return 0;
}


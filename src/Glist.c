#include <stdio.h>
#include <stdlib.h>
#include "Gtype.h"
#include "Glist.h"



int GlistInit(Glist** lst)
{

  *lst = (Glist *)malloc(sizeof(Glist));

  /*initializing the data */
  (*lst)->size = 0;
  (*lst)->first = (Gitem *)NULL;
  (*lst)->last =  (Gitem *)NULL;


  /*initializing the methods */
  (*lst)->add = GlistAdd;
  (*lst)->print = GlistPrint;
  (*lst)->del = GlistClear;
  (*lst)->erase = GlistDel;

  return 0;

}


 
int GlistAdd(Glist* lst, Gtype *opq)
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

void GlistPrint(Glist* lst)
{

  int itr;
  Gtype* gtp;
  Gitem *ptr;

  printf(" { ");
  itr = lst->size;
  for(ptr = lst->first; itr-- > 0; ptr = ptr->nxt)
    {
      gtp = (Gtype *)ptr->opq;
      gtp->print(gtp);
    }
  printf(" } ");

}

int GlistClear(Glist *lst)
{
  Gitem *ptr0 = NULL, *ptr1 = NULL;
  if ( lst->size )
    {
      for(ptr0 = lst->first; (ptr1 = ptr0->nxt) != NULL; ptr0 = ptr1)
	{
	  ptr0->opq->del(ptr0->opq);
	  free(ptr0);
	}
      ptr0->opq->del(ptr0->opq);
      free(ptr0);
    }

  free(lst);

  return 0;
}

int GlistDel(Glist *lst, int indx)
{
  int i;
  Gtype *tGtype = NULL;
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

  tGtype = (Gtype *)cur->opq;
  tGtype->del(tGtype);

  free(cur); 
  lst->size--;

  return 0;
}


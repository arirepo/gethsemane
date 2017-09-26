#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Gtype.h"
#include "Glist.h"
#include "Genv.h"


int GlistInit(Glist** lst)
{

  *lst = (Glist *)malloc(sizeof(Glist));

  /*initializing the data */
  (*lst)->size = 0;
  (*lst)->first = (Gitem *)NULL;
  (*lst)->last =  (Gitem *)NULL;

  (*lst)->itrs = (Gitem **)malloc(_DEFAULT_ITRS_SIZE_*sizeof(Gitem *));
  (*lst)->itrs_buff_size = _DEFAULT_ITRS_SIZE_;

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

  /* updating iterator table */
  if ( lst->size > lst->itrs_buff_size )
    if ( (lst->itrs 
	  = (Gitem **)realloc(lst->itrs
			     , (lst->itrs_buff_size += _DEFAULT_ITRS_SIZE_)*sizeof(Gitem *)))
	 == NULL)
      GERROR("Can't increase buffer size of the iterators table");

  lst->itrs[lst->size-1] = lst->last;

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

  free(lst->itrs);
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
  /* updating iterators table by shifting the addresses the left*/
  for( i=indx; i < lst->size; i++)
    lst->itrs[i] = lst->itrs[i+1];
  /* reduce the size of iterators table if too big */
  if ( (lst->size - lst->itrs_buff_size) > lst->itrs_buff_size )
    if ( (lst->itrs 
	  = (Gitem **)realloc(lst->itrs
			     , (lst->itrs_buff_size -= _DEFAULT_ITRS_SIZE_)*sizeof(Gitem *)))
	 == NULL)
      GERROR("Can't decrease buffer size of the iterators table");
 
  /* cleaning up the deleted element */
  tGtype = (Gtype *)cur->opq;
  tGtype->del(tGtype);

  free(cur); 
  lst->size--;

  return 0;
}

void Gsort(Gitem **A, int len)
{
  int piv;
  int i, j;
  Gitem *tmp;

  if (len < 2) return;
 
  piv = len / 2;
 
  for (i = 0, j = len - 1; ; i++, j--) 
    {
      while (A[i]->opq->rank(A[i]->opq) < A[piv]->opq->rank(A[piv]->opq)) i++;
      while (A[j]->opq->rank(A[j]->opq) > A[piv]->opq->rank(A[piv]->opq)) j--;
 
      if (i >= j) break;
 
      tmp = A[i];
      A[i] = A[j];
      A[j] =  tmp;

    }
 
  Gsort(A, i);
  Gsort((Gitem ** )(A + i), (len - i));

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Gtype.h"
#include "Glist.h"
#include "Genv.h"


int GlistInit(Glist** lst, void *top)
{

  *lst = (Glist *)malloc(sizeof(Glist));

  /*initializing the data */
  (*lst)->size = 0;
  (*lst)->first = (Gitem *)NULL;
  (*lst)->last =  (Gitem *)NULL;

  (*lst)->itrs = (Gitem **)malloc(_DEFAULT_ITRS_SIZE_*sizeof(Gitem *));
  (*lst)->itrs_buff_size = _DEFAULT_ITRS_SIZE_;

  /* setup the top Glist ; if any ... */
  (*lst)->top = top;

  /*initializing the methods */
  (*lst)->add = GlistAdd;
  (*lst)->print = GlistPrint;
  (*lst)->del = GlistDelete;
  (*lst)->erase = GlistErase;
  (*lst)->rank = GlistRank;

  return 0;

}


 
int GlistAdd(Glist* lst, void *opq, _GLIST_TYPE type, void *tag)
{

  Gitem *tail;
  Glist *gls;

  tail = lst->last;
  lst->last = (Gitem *) malloc( sizeof(Gitem) );
  if ( lst->last == NULL ) return 1; /* error code */

  lst->last->top = (void *)lst;
  if ( type == _GLIST_BRANCH )
    {
      gls = (Glist *)opq;
      gls->top = (void *)lst->last;
    }

  lst->last->type = type;
  lst->last->opq = opq;
  lst->last->tag = tag;

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
  Glist* gls;

  printf(" { ");
  itr = lst->size;
  for(ptr = lst->first; itr-- > 0; ptr = ptr->nxt)
    {
      /* printing the tag ; if any ... */
      if ( (gls = (Glist *)ptr->tag) != NULL)
	{
	  printf(" tag = ");
	  gls->print(gls);
	  printf(" , ");
	}

      if ( ptr->type == _GLIST_LEAF) /* then there is a Gtype here ... */
	{
	  gtp = (Gtype *)ptr->opq;
	  gtp->print(gtp);
	}
      else /* then there is a Glist here ... */
	{
	  gls = (Glist *)ptr->opq;
	  gls->print(gls);
	}
    }
  printf(" } ");

}

int GlistDelete(Glist *lst)
{
  Gitem *ptr0, *ptr1;
  Glist *gls;
  Gtype *gtp;

  if ( lst->size )
    {
      ptr0 = lst->first;
      do{

	  ptr1 = ptr0;
	  GitemDelete(ptr0);

	} while ( (ptr0 = ptr1->nxt) != NULL );

    }

  if ( lst->itrs != NULL )
    free(lst->itrs);

  free(lst);

  return 0;
}

int GlistErase(Glist *lst, int indx)
{
  int i;
  Gtype *tGtype;
  Gitem *cur;
  Glist *gls;

  cur = lst->first;
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
  GitemDelete(cur);

  lst->size--;

  return 0;
}

void GlistSort(Gitem **A, int len)
{
  int piv;
  int i, j;
  Gitem *tmp;


  if (len < 2) return;
 
  piv = len / 2;
 
  for (i = 0, j = len - 1; ; i++, j--) 
    {

      if (A[i]->type == _GLIST_LEAF)
	while ( ((Gtype *)A[i]->opq)->rank((Gtype *)A[i]->opq) 
		< ((Gtype *)A[piv]->opq)->rank((Gtype *)A[piv]->opq)) i++;
      else
	while ( ((Glist *)A[i]->opq)->rank((Glist *)A[i]->opq) 
		< ((Glist *)A[piv]->opq)->rank((Glist *)A[piv]->opq)) i++;

      if( A[j]->type == _GLIST_LEAF)
	while (((Gtype *)A[j]->opq)->rank((Gtype *)A[j]->opq) 
	       > ((Gtype *)A[piv]->opq)->rank((Gtype *)A[piv]->opq)) j--;
      else
	while (((Glist *)A[j]->opq)->rank((Glist *)A[j]->opq) 
	       > ((Glist *)A[piv]->opq)->rank((Glist *)A[piv]->opq)) j--;

 
      if (i >= j) break;
 
      tmp = A[i];
      A[i] = A[j];
      A[j] =  tmp;

    }
 
  GlistSort(A, i);
  GlistSort((Gitem ** )(A + i), (len - i));

}

void GitemDelete(Gitem *git)
{

  Gtype *gtp;
  Glist *gls;

  if ( git->tag != NULL)
    {
      gls = (Glist *)git->tag;
      gls->del(gls);
    }

  if ( git->type == _GLIST_LEAF )
    {
      gtp = (Gtype *)git->opq;
      gtp->del(gtp);
    }
  else
    {
      gls = (Glist *)git->opq;
      gls->del(gls);
    }


  free(git);

}

long double GlistRank(Glist *lst)
{
  return (long double)0.;
}

void GlistPrintItrs(Glist* lst)
{

  int itr;
  Gtype* gtp;
  Gitem *ptr;
  Glist* gls;

  printf(" { ");
  for(itr = 0; itr < lst->size; itr++)
    {
      ptr = lst->itrs[itr];

      /* printing the tag ; if any ... */
      if ( (gls = (Glist *)ptr->tag) != NULL)
	{
	  printf(" tag = ");
	  gls->print(gls);
	  printf(" , ");
	}

      if ( ptr->type == _GLIST_LEAF) /* then there is a Gtype here ... */
	{
	  gtp = (Gtype *)ptr->opq;
	  gtp->print(gtp);
	}
      else /* then there is a Glist here ... */
	{
	  gls = (Glist *)ptr->opq;
	  gls->print(gls);
	}
    }
  printf(" } ");

}

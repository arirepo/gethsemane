#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Gtype.h"
#include "Glist.h"
#include "Genv.h"


int GlistInit(Glist** lst, void *top)
{

  int ii;

  *lst = (Glist *)malloc(sizeof(Glist));

  /*initializing the data */
  (*lst)->size = 0;
  (*lst)->first = (Gitem *)NULL;
  (*lst)->last =  (Gitem *)NULL;

  (*lst)->itrs = (Gitem **)malloc(_DEFAULT_ITRS_SIZE_*sizeof(Gitem *));

  for( ii = 0; ii < _DEFAULT_ITRS_SIZE_; ii++)
    (*lst)->itrs[ii] = (Gitem *)NULL;

  (*lst)->itrs_buff_size = _DEFAULT_ITRS_SIZE_;

  /* setup the top Glist ; if any ... */
  (*lst)->top = top;

  /*initializing the methods */
  (*lst)->add = GlistAdd;
  (*lst)->print = GlistPrintItrs;
  (*lst)->del = GlistDelete;
  (*lst)->erase = GlistErase;
  (*lst)->rank = GlistRank;
  (*lst)->find = GlistFind;
  (*lst)->refresh = GlistRefresh;
  (*lst)->sort = GlistSortMethod;
  (*lst)->index = GlistIndex;
  (*lst)->clone = GlistClone;

  return 0;

}


 
int GlistAdd(Glist* lst, void *opq, _GLIST_TYPE type, Gtype *tag)
{

  Gitem *tail;
  Glist *gls;

  tail = lst->last;
  lst->last = (Gitem *) malloc( sizeof(Gitem) );
  if ( lst->last == NULL ) return 1; /* error code */

  lst->last->tag = tag;
  lst->last->top = (void *)lst;
  if ( type == _GLIST_BRANCH )
    {
      gls = (Glist *)opq;
      gls->top = (void *)lst->last;
    }

  lst->last->type = type;
  lst->last->opq = opq;

  if ( lst->size == 0 ) /* if the list is currently empty */
    {
      lst->first = lst->last;
      lst->first->nxt = NULL;
      lst->first->prv = NULL;
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
      if ( (gtp = (Gtype *)ptr->tag) != NULL)
	{
	  printf(" tag = ");
	  gtp->print(gtp);
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

  if ( lst->size )
    {
      ptr0 = lst->first;
      do{

	  ptr1 = ptr0->nxt;
	  GitemDelete(ptr0);

	} while ( (ptr0 = ptr1) != NULL );

    }

  lst->first = NULL;
  lst->last  = NULL;

  if ( lst->itrs != NULL )
    free(lst->itrs);

  lst->itrs = NULL;
  lst->itrs_buff_size = 0;

  lst->top = NULL;

  lst->add = NULL;
  lst->print = NULL;
  lst->del = NULL;
  lst->erase = NULL;
  lst->rank = NULL;
  lst->find = NULL;
  lst->refresh = NULL;
  lst->sort = NULL;
  lst->index = NULL;
  lst->clone = NULL;

  free(lst);
  lst = NULL;

  return 0;
}

int GlistErase(Glist *lst, int indx)
{
  int i;
  Gitem *cur;

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
#ifdef DEBUG_VERBOSE
      GECHO("deleting the tag ...");
#endif
      gtp = (Gtype *)git->tag;
      gtp->del(gtp);
    }

  git->top = NULL;

  if ( git->type == _GLIST_LEAF )
    {
#ifdef DEBUG_VERBOSE
      GECHO("deleting the leaf ...");
#endif

      gtp = (Gtype *)git->opq;
      gtp->del(gtp);
    }
  else
    {
#ifdef DEBUG_VERBOSE
      GECHO("deleting the branch ...");
#endif

      gls = (Glist *)git->opq;
      gls->del(gls);
    }

  git->prv = NULL;
  git->nxt = NULL;

  free(git);

  git = NULL;

}

 double GlistRank(Glist *lst)
{
  /* return ( double)0.; */
   double rank;
  Gitem *itr;

  for( rank = 0., itr = lst->first; itr != NULL; itr = itr->nxt)
    rank += ( ( itr->type == _GLIST_LEAF)?1.:GlistRank((Glist *)itr->opq) );

  return rank; 
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
      if ( (gtp = (Gtype *)ptr->tag) != NULL)
	{
	  printf(" tag = ");
	  gtp->print(gtp);
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

void GlistFind(Glist *lst, Gtype *val, int num, Glist *res)
{

  Gitem *itr;
  Gtype *gtp;


  for (itr = lst->first; ((itr != NULL) && (res->size < num)); itr = itr->nxt)
    if ( itr->type == _GLIST_LEAF )
      {
	if ( ((Gtype *)(itr->opq))->cmp((Gtype *)(itr->opq), val) == 0 )
	  {
	    GtypeInit(&gtp, sizeof(Gitem *));
	    gtp->set(gtp, itr, sizeof(Gitem *));
	    res->add(res, gtp, _GLIST_LEAF, NULL);
	  }
      }
    else
      ((Glist *)(itr->opq))->find(((Glist *)(itr->opq)), val, num, res);

}

void GlistRefresh(Glist *lst)
{
  void *topp;
  topp = NULL;

  topp = lst->top;
  lst->del(lst);
  GlistInit(&lst, topp);

}

void GlistSortMethod(Glist *lst)
{

  GlistSort(lst->itrs, lst->size);

}

Gitem *GlistIndex(Glist *lst, int indx, _GLIST_TYPE alg)
{

  int i;
  Gitem *res;
  res = NULL;

  switch ( alg )
    {
    case _GLIST_INDEX_NO_SORT:
      for ( i= 0 , res = lst->first; ((res != NULL) && (i < indx)); i++, res = res->nxt);

      break;
    case _GLIST_INDEX_SORTED:

      res = lst->itrs[indx];

      break;
    default:

      GERROR("\n Unknown indexing algorithm! \n");

    }

  return res;

}

Glist *GlistClone(Glist *this, Glist *that)
{

  Gtype *gtp, *ttag;
  Gitem *git;
  Glist *gls;

  this->del(this);
  GlistInit(&this, that->top);

  gtp = NULL;
  ttag = NULL;
  gls = NULL;
  GlistInit(&gls, NULL);


  for( git = that->first; git != NULL; git = git->nxt)
    {

      if ( git->tag != NULL )
	{ 

	  GtypeInit(&ttag, git->tag->nb);
	  ttag->assign(ttag, git->tag);
	}	

      switch ( git->type )
	{ 
	case _GLIST_BRANCH:

	  gls->clone(gls, (Glist *)git->opq);
	  this->add(this, gls, _GLIST_BRANCH, ttag);
	  break;

	case _GLIST_LEAF:

	  GtypeInit(&gtp, ((Gtype *)git->opq)->nb);
	  gtp->assign(gtp, (Gtype *)git->opq);
	  this->add(this, gtp, _GLIST_LEAF, ttag);
	  break;

	default:

	  GERROR("\n Unknown GLIST TYPE, must be either BRANCH or LEAF \n");

	}

    }

  /* cloning the methods */
  this->add     = that->add;
  this->print   = that->print;
  this->del     = that->del;
  this->erase   = that->erase;
  this->rank    = that->rank;
  this->find    = that->find;
  this->refresh = that->refresh;
  this->sort    = that->sort;
  this->index   = that->index;
  this->clone   = that->clone;

  return this;
}

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Gtype.h"
#include "Genv.h"

int GtypeInit(Gtype **inp, size_t nb)
{

  *inp = (Gtype *)malloc(sizeof(Gtype));

  (*inp)->nb = nb;
  (*inp)->opq = (void *)malloc(nb);

  if ( (*inp)->opq == NULL ) return 1;


  /* setup foundation functions */
  (*inp)->get = GtypeGet;
  (*inp)->del = GtypeDel;
  (*inp)->set = GtypeSet;
  (*inp)->print = GtypePrint;
  (*inp)->rank = GtypeRank;
  (*inp)->cmp = GtypeCmp;
  (*inp)->assign = GtypeAssign;
  (*inp)->clone = GtypeClone;
  (*inp)->refresh = GtypeRefresh;


  /* setup  all other methods */
  (*inp)->vtable = NULL;

  return 0;

}

void *GtypeGet(Gtype *inp)
{

  return (void*)inp->opq;

}


int GtypeDel(Gtype *inp)
{

  inp->nb = 0;
  free(inp->opq);
  inp->opq = NULL;

  inp->get = NULL;
  inp->del = NULL;
  inp->set = NULL;
  inp->print = NULL;
  inp->rank = NULL;
  inp->cmp = NULL;
  inp->assign = NULL;
  inp->clone = NULL;
  inp->refresh = NULL;

  inp->vtable = NULL;

  free(inp);
  
  inp = NULL;  

  return 0;
}

void *GtypeSet(Gtype *inp, void *val, size_t nb)
{

  inp->nb = nb;
  memcpy ( inp->opq, val, nb );

  return (void*)inp->opq;
}

void GtypePrint(Gtype *inp)
{

  printf(" [%p] ", (void *)inp->opq);

}

int GtypeInitBasic(Gtype **inp, _GTYPE_TYPE typ)
{

  *inp = (Gtype *)malloc(sizeof(Gtype));

  switch (typ)
    {
    case     _GTYPE_INT:
 
      (*inp)->nb = sizeof(int);
      (*inp)->opq = (int *)malloc(sizeof(int));

      /* setup foundation functions */
      (*inp)->get = GtypeGetInt;
      (*inp)->print = GtypePrintInt;
      (*inp)->rank = GtypeRankInt;

      break;
    case     _GTYPE_FLOAT:
 
      (*inp)->nb = sizeof(float);
      (*inp)->opq = (float *)malloc(sizeof(float));

      /* setup foundation functions */
      (*inp)->get = GtypeGetFloat;
      (*inp)->print = GtypePrintFloat;
      (*inp)->rank = GtypeRankFloat;

      break;
    case     _GTYPE_DOUBLE:
 
      (*inp)->nb = sizeof(double);
      (*inp)->opq = (double *)malloc(sizeof(double));

      /* setup foundation functions */
      (*inp)->get = GtypeGetDouble;
      (*inp)->print = GtypePrintDouble;
      (*inp)->rank = GtypeRankDouble;

      break;

    default:
      GERROR("\n Unknown basic data type! \n");
    }

  /* the following are the same for all instances */
  (*inp)->del = GtypeDel;
  (*inp)->set = GtypeSet;
  (*inp)->cmp = GtypeCmp;
  (*inp)->assign = GtypeAssign;
  (*inp)->clone = GtypeClone;
  (*inp)->refresh = GtypeRefresh;

  /* setup  all other methods */
  (*inp)->vtable = NULL;

  return 0;

}

int *GtypeGetInt(Gtype *inp)
{

  return (int*)inp->opq;

}

void GtypePrintInt(Gtype *inp)
{

  printf(" %d ", *(int *)inp->opq);

}

float *GtypeGetFloat(Gtype *inp)
{

  return (float*)inp->opq;

}

void GtypePrintFloat(Gtype *inp)
{

  printf(" %f ", *(float *)inp->opq);

}

double *GtypeGetDouble(Gtype *inp)
{

  return (double*)inp->opq;

}

void GtypePrintDouble(Gtype *inp)
{

  printf(" %16.16f ", *(double *)inp->opq);

}


 double GtypeRank(Gtype *inp)
{

  return *( double*)inp->opq;

}

 double GtypeRankInt(Gtype *inp)
{

  int tmp;
  tmp = *(int *)inp->opq;
  return ( double)tmp;

}

 double GtypeRankFloat(Gtype *inp)
{

  float tmp;
  tmp = *(float *)inp->opq;
  return ( double)tmp;

}

 double GtypeRankDouble(Gtype *inp)
{

  double tmp;
  tmp = *(double *)inp->opq;
  return ( double)tmp;

}

int GtypeCmp(Gtype *inp, Gtype *tp)
{

  assert( inp->nb == tp->nb );

  return memcmp( inp->opq, tp->opq, inp->nb);

}

int GtypeAssign(Gtype *this, const Gtype *that)
{

  assert(this->nb == that->nb);
  this->set(this, that->opq, that->nb);

  /* foundation methods */
  this->get = that->get;
  this->del = that->del;
  this->set = that->set;
  this->print = that->print;
  this->rank = that->rank;
  this->cmp = that->cmp;
  this->assign = that->assign;
  this->clone = that->clone;
  this->refresh = that->refresh;

  /* vtable - array of (void *) pointers to user-defined methods*/
  /*                object holder     arguments                 */
  this->vtable = that->vtable;


  return 0;
}

int GtypeClone(Gtype* this, const Gtype* that)
{
 
  this->del(this);
  GtypeInit(&this, that->nb);

  this->assign(this, that);

  return 0;
}

int GtypeRefresh(Gtype *this)
{
  size_t nb;

  nb = this->nb;

  this->del(this);
  GtypeInit(&this, nb);

  return 0;
}

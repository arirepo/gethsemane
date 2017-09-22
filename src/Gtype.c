#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Gtype.h"
#include "Genv.h"

int GtypeInit(Gtype **inp, size_t nb)
{

  *inp = (Gtype *)malloc(sizeof(Gtype));

  (*inp)->opq = (void *)malloc(nb);

  if ( (*inp)->opq == NULL ) return 1;

  (*inp)->nested = 0;

  /* setup foundation functions */
  (*inp)->get = GtypeGet;
  (*inp)->del = GtypeDel;
  (*inp)->set = GtypeSet;
  (*inp)->print = GtypePrint;

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
  Gtype *sub = NULL;

  if (inp->nested)
    {
      sub = (Gtype *)inp->opq;
      sub->del(sub);
    }
  else
    {
      free(inp->opq);
      inp->nested = 0;

      inp->get = NULL;
      inp->del = NULL;
      inp->vtable = NULL;

      free(inp);
    }

  return 0;
}

void *GtypeSet(Gtype *inp, void *val, size_t nb)
{
  memcpy ( inp->opq, val, nb );

  return (void*)inp->opq;
}

void GtypePrint(Gtype *inp)
{

  printf(" [%p] ", (void *)inp->opq);

}

int GtypeInitBasic(Gtype **inp, _G_BASIC typ)
{

  *inp = (Gtype *)malloc(sizeof(Gtype));

  switch (typ)
    {
    case     _G_INT:
 
      (*inp)->opq = (int *)malloc(sizeof(int));

      /* setup foundation functions */
      (*inp)->get = GtypeGetInt;
      (*inp)->print = GtypePrintInt;

      break;
    case     _G_FLOAT:
 
      (*inp)->opq = (float *)malloc(sizeof(float));

      /* setup foundation functions */
      (*inp)->get = GtypeGetFloat;
      (*inp)->print = GtypePrintFloat;

      break;
    case     _G_DOUBLE:
 
      (*inp)->opq = (double *)malloc(sizeof(double));

      /* setup foundation functions */
      (*inp)->get = GtypeGetDouble;
      (*inp)->print = GtypePrintDouble;

      break;

    default:
      GERROR("\n Unknown basic data type! \n");
    }

  /* the following are the same for all instances */
  (*inp)->nested = 0;
  (*inp)->del = GtypeDel;
  (*inp)->set = GtypeSet;

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

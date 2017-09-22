#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Gtype.h"

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

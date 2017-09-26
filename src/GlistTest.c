#include <stdio.h>
#include "Gtype.h"
#include "Glist.h"



int main(int argc, char *argv[])
{

  int ii;
  float fval;
  double dval;

  /* _GTYPE(inp); */
  /* _GTYPE(inp2); */
  /* _GLIST(lst); */
  Gtype *inp, *inp2, *inp3, *inp4, *inp5;
  Glist *lst;
  Gtype *tGtype;

  GtypeInit(&inp, sizeof(int));
  GtypeInit(&inp2, sizeof(int));
  GtypeInitBasic(&inp3, _G_INT);
  GtypeInitBasic(&inp4, _G_FLOAT);
  GtypeInitBasic(&inp5, _G_DOUBLE);

  GlistInit(&lst);


  /* for( ii= 0; ii < 100000; ii++) */
  /*   { */
  ii = 4;
  inp->set(inp, &ii, sizeof(int));
  ii = 5;
  inp2->set(inp2, &ii, sizeof(int));
  ii = 6;
  inp3->set(inp3, &ii, sizeof(int));

  fval = 18.35;
  inp4->set(inp4, &fval, sizeof(float));

  dval = -1.28783487845;
  inp5->set(inp5, &dval, sizeof(double));

  lst->add(lst, inp);
  lst->add(lst, inp3);
  lst->add(lst, inp5);
  lst->add(lst, inp2);
  lst->add(lst, inp4);



    /* } */

  /* for( ii= 0; ii < 100000; ii++) */
  lst->erase(lst, 0);

  GlistPrint(lst);

  Gsort(lst->itrs, lst->size);

  for ( ii = 0; ii < lst->size; ii++)
    {
      tGtype = (Gtype *)lst->itrs[ii]->opq; 
      tGtype->print(tGtype);
      printf(" *%f* ", (double)tGtype->rank(tGtype));
    }

  printf("\n argc = %d \n", argc);
  printf("argv[0] = %s \n" , argv[0]);


  lst->del(lst);

  return 0;
}

#include <stdio.h>
#include "Gtype.h"
#include "Glist.h"



int main(int argc, char *argv[])
{

  int ii;
  /* _GTYPE(inp); */
  /* _GTYPE(inp2); */
  /* _GLIST(lst); */
  Gtype *inp, *inp2;
  Glist *lst;

  GtypeInit(&inp, sizeof(int));
  GtypeInit(&inp2, sizeof(int));
  GlistInit(&lst);


  /* for( ii= 0; ii < 100000; ii++) */
  /*   { */
  ii = 4;
  inp->set(inp, &ii, sizeof(int));
  ii = 5;
  inp->set(inp2, &ii, sizeof(int));

  lst->add(lst, inp);
  lst->add(lst, inp2);

    /* } */

  /* for( ii= 0; ii < 100000; ii++) */
  /* lst->erase(lst, 0); */

  GlistPrint(lst);


  printf("\n argc = %d \n", argc);
  printf("argv[0] = %s \n" , argv[0]);


  lst->del(lst);

  return 0;
}

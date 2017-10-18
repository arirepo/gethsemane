#include <stdio.h>
#include "Gtype.h"


int main(int argc, char *argv[])
{

  int ii;
  Gtype *inp;
  Gtype *inp2;

  GtypeInit(&inp, sizeof(int));
  GtypeInitBasic(&inp2, _GTYPE_INT);

  for ( ii = 0; ii < 1000; ii++)
    {
      inp->set(inp, &ii, sizeof(int));
      printf("\n value = %d \n", *(int *)inp->get(inp));

      inp2->set(inp2, &ii, sizeof(int));
      inp2->print(inp2);

    }

  inp->del(inp);
  inp2->del(inp2);

  printf("\n argc = %d \n", argc);
  printf("argv[0] = %s \n" , argv[0]);


  return 0;
}

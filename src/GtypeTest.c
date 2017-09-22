#include <stdio.h>
#include "Gtype.h"


int main(int argc, char *argv[])
{

  int ii;
  /* _GTYPE(inp); */
  Gtype *inp;

  GtypeInit(&inp, sizeof(int));
  for ( ii = 0; ii < 1000; ii++)
    {
      inp->set(inp, &ii, sizeof(int));
      printf("\n value = %d \n", *(int *)inp->get(inp));
    }

  inp->del(inp);

  printf("\n argc = %d \n", argc);
  printf("argv[0] = %s \n" , argv[0]);


  return 0;
}

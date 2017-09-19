#include <stdio.h>
#include "Glist.h"

struct dummy_int
{
  int value;
  double value2;
};

/* typedef int Dint; */
typedef double Dint;
/* typedef struct dummy_int Dint; */


int main(int argc, char *argv[])
{

  int ii; 
  Dint *aDint = NULL;
  _GLIST(lst);


  Glist_init_zero(lst);


  for( ii= 0; ii < 100000; ii++)
    {
      aDint = (Dint *)malloc(sizeof(Dint));
      Glist_add(lst, (void *)aDint);
    }

  for( ii= 0; ii < 100000; ii++)
    Glist_delete(lst, 0);


  printf("\n argc = %d \n", argc);
  printf("argv[0] = %s \n" , argv[0]);

  Glist_print("lst = ", lst);

  Glist_clear(lst);

  return 0;
}

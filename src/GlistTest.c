#include <stdio.h>
#include "Glist.h"

int main(int argc, char *argv[])
{

int ii;

_GLIST(lst);
Glist_init_zero(lst);

for( ii= 0; ii < 10; ii++)
  Glist_add(lst, ii);

Glist_delete(lst, 9);
Glist_print("lst", lst);

printf("\n argc = %d \n", argc);
printf("argv[0] = %s \n" , argv[0]);

Glist_clear(lst);

return 0;
}

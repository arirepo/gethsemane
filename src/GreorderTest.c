#include <stdio.h>
#include "Glist.h"
#include "Greorder.h"

int main(int argc, char *argv[])
{

  Glist *verts, *neigh, *R, *Q;

  /* creating a sample graph */


  /*reorder */
  GCuthillMcKee(verts, R, Q);


  return 0;
}



#include <stdio.h>
#include "Glist.h"
#include "Gcart.h"
#include "Greorder.h"

int main(int argc, char *argv[])
{

  Glist *verts, *neigh, *R, *Q;

  GlistInit(&verts, NULL);
  /* creating a sample graph */
  GcartGraph2d(verts, 10, 10);
  verts->print(verts);

  /*reorder */
  GCuthillMcKee(verts, R, Q);

  /* clean ups */
  verts->del(verts);

  return 0;
}



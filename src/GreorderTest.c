#include <stdio.h>
#include "Glist.h"
#include "Gcart.h"
#include "Greorder.h"
#include "Genv.h"

int main(int argc, char *argv[])
{

  Glist *verts, *neigh, *R, *Q;

  GlistInit(&verts, NULL);
  /* creating a sample graph */
  GcartGraph2d(verts, 3, 3);

  GECHO("\n Before sort ... \n");
  verts->print(verts);

  GlistSort(verts->itrs, verts->size);

  GECHO("\n After sort ... \n");
  verts->print(verts);

  /*reorder */
  GCuthillMcKee(verts, R, Q);

  /* clean ups */
  verts->del(verts);

  return 0;
}



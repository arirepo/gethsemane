#include <stdio.h>
#include "Glist.h"
#include "Gcart.h"
#include "Greorder.h"
#include "Genv.h"
#include "Gtype.h"

int main(int argc, char *argv[])
{

  Glist *verts, *neigh, *R, *Q;
  Glist *fnds;
  Gtype *gtp;
  int ii;

  GlistInit(&verts, NULL);
  /* creating a sample graph */
  GcartGraph2d(verts, 3, 3);

  GECHO("\n Before sort ... \n");
  verts->print(verts);

  GlistSort(verts->itrs, verts->size);

  GECHO("\n After sort ... \n");
  verts->print(verts);

  ii = 4;
  GtypeInitBasic(&gtp, _GTYPE_INT);
  gtp->set(gtp, &ii, sizeof(int));

  GlistInit(&fnds, NULL);
  verts->find(verts, gtp, 10, fnds);

  fflush(stdout);

  fnds->print(fnds);

  /*reorder */
  GCuthillMcKee(verts, R, Q);

  /* clean ups */
  verts->del(verts);
  fnds->del(fnds);
  gtp->del(gtp);

  return 0;
}



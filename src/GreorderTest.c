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

  fnds->del(fnds);
  GlistInit(&fnds, NULL);

  /* for(ii = fnds->size; ii > 0; ii--) */
  /*   fnds->erase(fnds, 0); */

  verts->find(verts, gtp, 10, fnds);


  fnds->print(fnds);
  fflush(stdout);

  /*reorder */
  GCuthillMcKee(verts, R, Q);

  /* clean ups */
  fnds->del(fnds);
  verts->del(verts);
  gtp->del(gtp);

  return 0;
}



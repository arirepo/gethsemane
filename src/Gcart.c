#include <assert.h>
#include "Gcart.h"
#include "Gtype.h"
#include "Glist.h"


int GcartGraph2d(Glist *lst, int nx, int ny)
{

  int i, j, ii, k;
  int vall;
  Glist *gls;
  Gtype **neigh;

  neigh = (Gtype **)malloc(4 * sizeof(Gtype *));

  /* check the min size of the network */
  assert( (nx > 1) && (ny > 1) );

  /* add nodes to the list */
  for(i=0; i < (nx*ny); i++)
    {
      GlistInit(&gls, lst);
      lst->add(lst, gls, _GLIST_BRANCH, NULL);
    }

  ii = 0; /* first node number */
  for( j = 0; j < ny; j++)
    for( i = 0; i < nx; i++)
      {
	/* get hold on the current node ... */
	gls = (Glist *)(lst->itrs[ii])->opq;

	/* generate possible neighbors using Cartesian rule*/
	for ( k = 0; k < 4; k++)
	  GtypeInitBasic(&neigh[k], _GTYPE_INT);

	vall = (i == (nx-1) )?(-1):(ii + 1);
	neigh[0]->set(neigh[0], &vall, sizeof(int));

	vall = (j == (ny-1) )?(-1):(ii + nx);
	neigh[1]->set(neigh[1], &vall, sizeof(int));

	vall = (i == 0)?(-1):(ii-1);
	neigh[2]->set(neigh[2], &vall, sizeof(int));

	vall = (j == 0)?(-1):(ii - nx);
	neigh[3]->set(neigh[3], &vall, sizeof(int));

	for ( k = 0; k < 4; k++)
	  if ( *((int *)neigh[k]->get(neigh[k])) == -1 ) /* wall */
	    neigh[k]->del(neigh[k]);
	  else
	    gls->add(gls, neigh[k], _GLIST_LEAF, NULL);

	/* next node */
	ii++;
      }

  free(neigh);

  return 0;
}

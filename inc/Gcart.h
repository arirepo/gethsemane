#ifndef _GCART_H_
#define _GCART_H_

#include "Glist.h"

/* creates a 2d cartesian network containing 
nodes n(ij) with nx number of nodes in the x-direction
and ny number of nodes in the y-direction */
int GcartGraph2d(Glist *lst, int nx, int ny);

#endif

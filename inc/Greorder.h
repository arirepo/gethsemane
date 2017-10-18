#ifndef _GREORDER_H_
#define _GREORDER_H_

#include "Glist.h"

/* implements the Cuthill - McKee algorithm
   for a graph represented by the connectivity matrix 
   stored in the Glist format*/ 
int GCuthillMcKee(Glist *verts, Glist *R, Glist *Q);


#endif

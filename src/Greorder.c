#include <stdio.h>
#include "Genv.h"
#include "Greorder.h"
#include "Glist.h"

int GCuthillMcKee(Glist *verts, Glist *R)
{

  int i, itr, Pfound;
  Gtype *P, *Qn;
  Gitem *git, *git2;
  Glist *Q, *inR, *nPdeg;

  /* resetting the output list */
  R->refresh(R);
  GlistInit(&Q, NULL);
  GlistInit(&inR, NULL);
  GlistInit(&nPdeg, NULL);

  /* sort vertices to find the vertex with smallest degree */
  verts->sort(verts);

  /* get tag which is the vertex number (ZERO-BASED) */
  GtypeInitBasic(&P, _GTYPE_INT);
  P->clone(P, verts->first->tag);

  /* continue creating the queue and adding eligible nodes to R */  
  for ( Q->refresh(Q), itr = 0; (Q->size || (itr == 0) ); ((itr)?Q->erase(Q,0):0), itr++)
    {

      if ( itr ) /* check to see if P is already in R */
	{
	  GtypeInitBasic(&P, _GTYPE_INT);
	  P->assign(P, (Gtype *)(Q->first->opq));
	  /* P->assign(P, (Gtype *)(Q->first->opq)); */
	  inR->refresh(inR);
	  R->find(R, P, 1, inR);
	  Pfound = (inR->size) ? 1 : 0;
	}

      if ( !Pfound || !itr ) /* if P is not in R already, then add it */
	{
	  /* add P to R */
	  R->add(R, P, _GLIST_LEAF, NULL);

	  /* sort and add neighbors of P to Q */
	  /* find the Gitem of the P node in the original (unsorted) vertices-list */
	  git = verts->index(verts, *((int *)P->get(P)), _GLIST_INDEX_NO_SORT);
	  nPdeg->clone(nPdeg, (Glist *)git->opq);

	  /* finding the degrees of each neighboring node, then set: 
	     tag = node number of that neighbor
	     opq = size of the neighbors of that neighbor
	  */
	  for ( git = nPdeg->first; git != NULL; git= git->nxt)
	    {
	      (git->tag)->set(git->tag
				       , ((Gtype *)git->opq)->get((Gtype *)(git->opq))
				       , sizeof(int)); 
	      git2 = verts->index(verts, *(int *)((Gtype *)git->opq)->get((Gtype *)git->opq)
				  , _GLIST_INDEX_NO_SORT);
	      ((Gtype *)(git->opq))->set((Gtype *)(git->opq), 
					 &((Glist *)(git2->opq))->size, sizeof(int));
	    }
  
	  nPdeg->sort(nPdeg);

	  for ( i=0; i < nPdeg->size; i++)
	    {
	      GtypeInitBasic(&Qn, _GTYPE_INT);
	      Qn->assign(Qn, (Gtype *)((nPdeg->index(nPdeg, i, _GLIST_INDEX_SORTED))->tag));
	      Q->add(Q, Qn, _GLIST_LEAF, NULL);
	    }

	}
    }

  /* clean ups */
  Q->del(Q);
  inR->del(inR);
  nPdeg->del(nPdeg);

  return 0;

}


#ifndef _GLIST_
#define _GLIST_
#include <stdlib.h>

/*
Defining the basic linked-list datatype 
*/

struct opq_item {

  /* item */
  /* int num; */
  void *opq;

  struct opq_item* prv;
  struct opq_item* nxt;
};

typedef struct opq_item Gitem; 


/*
Defining the entire linked-list 
*/

struct opq_list {

  int size;
  Gitem* first;
  Gitem* last;
};

/* alias name for opq_list structure */ 
typedef struct opq_list Glist;

/* init a Glist struct to zero*/
int Glist_init_zero(Glist* lst);

/* macros */
#define _GLIST(lst) Glist *lst = (Glist *) malloc( sizeof(Glist) );



/* adds an opaque object to the opaque list
   on success return 0 else return the error code */

int Glist_add(Glist* lst, void *opq);

/* prints the components of the Glist struct */
int Glist_print(char *name, Glist* lst);

/* cleans up the entire memory dedicated to the list */ 
int Glist_clear(Glist *lst);

/* deletes specific item located at the indx'th location (zero-based)
   in the Glist */
int Glist_delete(Glist *lst, int indx);

#endif

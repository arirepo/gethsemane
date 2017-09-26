#ifndef _GLIST_
#define _GLIST_
#include <stdlib.h>
#include "Gtype.h"

/*
Defining the basic linked-list datatype 
*/

struct opq_item {

  /* item */
  /* int num; */
  Gtype *opq;

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
  /* C++ style iterators for direct access to the list elements*/
  Gitem** itrs;
#ifndef _DEFAULT_ITRS_SIZE_
#define _DEFAULT_ITRS_SIZE_ 100
#endif
  int itrs_buff_size;

  /* methods */
  int (*add)(struct opq_list* , Gtype *);
  void (*print)(struct opq_list*);
  int (*del)(struct opq_list* );
  int (*erase)(struct opq_list *, int);

};

/* alias name for opq_list structure */ 
typedef struct opq_list Glist;


/* /\* macros *\/ */
/* #define _GLIST(lst) Glist *lst = (Glist *) malloc( sizeof(Glist) ); */

/* init a Glist struct to zero*/
int GlistInit(Glist** lst);


/* adds an opaque object to the opaque list
   on success return 0 else return the error code */
int GlistAdd(Glist* lst, Gtype *opq);

/* prints the components of the Glist struct */
void GlistPrint(Glist* lst);

/* cleans up the entire memory dedicated to the list */ 
int GlistClear(Glist *lst);

/* deletes specific item located at the indx'th location (zero-based)
   in the Glist */
int GlistDel(Glist *lst, int indx);

/* sorts a Glist using the value provided by ->get() method
   implements a quicksort algorithm and sorts the iterators table*/
void Gsort(Gitem **A, int len);

#endif

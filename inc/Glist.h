#ifndef _GLIST_
#define _GLIST_
#include <stdlib.h>


/* basic datatypes used in Glist */
enum glist_type
  {
    _GLIST_BRANCH,
    _GLIST_LEAF
  };
typedef enum glist_type _GLIST_TYPE;


struct opq_item {

  /* tag is the optional value of this node 
     it can also be another Glist as a tag!*/ 
  void *tag;

  /* can have another Glist as top (parrent) ... */
  void * top;
  /* opq can be either another Glist when type = _GLIST_BRANCH 
     or Gtype when reaching to the leaf, i.e. type = _GLIST_LEAF */
  _GLIST_TYPE type;
  void *opq;

  struct opq_item* prv;
  struct opq_item* nxt;
};

typedef struct opq_item Gitem; 


/*
Defining the entire tree-like linked-list 
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

  /* top Glist ; if any ... 
     it should point to the Gitem that holds this Glist*/
  void *top;

  /* methods */
  int (*add)(struct opq_list* , void *, _GLIST_TYPE, void *);
  void (*print)(struct opq_list*);
  int (*del)(struct opq_list* );
  int (*erase)(struct opq_list *, int);
  long double (*rank)(struct opq_list *);
};

/* alias name for opq_list structure */ 
typedef struct opq_list Glist;


/* deletes (clears up) a Gitem from memory */
void GitemDelete(Gitem *git);

/* /\* macros *\/ */
/* #define _GLIST(lst) Glist *lst = (Glist *) malloc( sizeof(Glist) ); */

/* init a Glist struct to zero*/
int GlistInit(Glist** lst, void *top);

/* adds an opaque object to the opaque list
   on success return 0 else return the error code */
int GlistAdd(Glist* lst, void *opq, _GLIST_TYPE type, void *tag);

/* prints the components of the Glist struct */
void GlistPrint(Glist* lst);

/* cleans up the entire memory dedicated to the list */ 
int GlistDelete(Glist *lst);

/* deletes specific item located at the indx'th location (zero-based)
   in the Glist */
int GlistErase(Glist *lst, int indx);

/* sorts a Glist using the value provided by ->get() method
   implements a quicksort algorithm and sorts the iterators table*/
void GlistSort(Gitem **A, int len);


/* returns the rank of current Glist 
define your own specific procedure here ...
*/
long double GlistRank(Glist *);

void GlistPrintItrs(Glist*);

#endif

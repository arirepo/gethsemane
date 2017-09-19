#ifndef _INT_ITEM_
#define _INT_ITEM_

/*
Defining the basic integer linked-list datatype 
*/

struct int_item {

  /* item */
  int num;

  struct int_item* prv;
  struct int_item* nxt;
};

typedef struct int_item Gitem; 


#endif


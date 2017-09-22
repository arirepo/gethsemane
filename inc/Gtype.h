#ifndef _GTYPE_H_
#define _GTYPE_H_
#include <stdlib.h>

/* definition of a generic class datatype */

struct gen_class
{
  /* data part */
  void *opq;
  /* is zero if the object only contains primitive types
     and is nonzero if the opaque pointer in the object points to another
     object of gen_class */ 
  short nested;

  /* foundation methods */
  void* (*get)(struct gen_class *);
  int   (*del)(struct gen_class *);
  void* (*set)(struct gen_class *, void *, size_t);
  void (*print)(struct gen_class *);

  /* vtable - array of (void *) pointers to user-defined methods*/
  /*                object holder     arguments                 */
  void **(*vtable)(struct gen_class *, void *, size_t );


};

typedef struct gen_class Gtype;

/* /\* macros *\/ */
/* #define _GTYPE(typ) Gtype *typ = (Gtype *) malloc( sizeof(Gtype) ); */

/* functions */

/* initializes a non-nested object */
int GtypeInit(Gtype **inp, size_t nb);

/* a generic get operator */
void *GtypeGet(Gtype *inp);

/* a full memory garbage collector */
int GtypeDel(Gtype *inp);

/* set an arbitrary given value at the opaque pointer of the current object */
void *GtypeSet(Gtype *inp, void *val, size_t nb);

/* generic printer; prints the pointer address to the opaque data of the input, i.e. inp
   when the data type is not specified */
void GtypePrint(Gtype *inp);

#endif


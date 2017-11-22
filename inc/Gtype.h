#ifndef _GTYPE_H_
#define _GTYPE_H_
#include <stdlib.h>

/* basic datatypes used in Gtype */
enum gtype_type
  {
    _GTYPE_INT,
    _GTYPE_FLOAT,
    _GTYPE_DOUBLE
  };
typedef enum gtype_type _GTYPE_TYPE;

/* definition of a generic class datatype */

struct gen_class
{
  /* data part */
  size_t nb; /*number of bytes in opaue data */
  void *opq;

  /* foundation methods */
  void* (*get)(struct gen_class *);
  int   (*del)(struct gen_class *);
  void* (*set)(struct gen_class *, void *, size_t);
  void (*print)(struct gen_class *);
   double (*rank)(struct gen_class *);
  int (*cmp)(struct gen_class *, struct gen_class *);
  int (*assign)(struct gen_class *, const struct gen_class *);
  int (*clone)(struct gen_class *, const struct gen_class *);
  int (*refresh)(struct gen_class *);

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

/* initializes a Gtype which has a specific basic datatype given by the user 
   the datatype must be selected from _GTYPE_TYPE enum by user */
int GtypeInitBasic(Gtype **inp, _GTYPE_TYPE typ);


int *GtypeGetInt(Gtype *inp);
void GtypePrintInt(Gtype *inp);
float *GtypeGetFloat(Gtype *inp);
void GtypePrintFloat(Gtype *inp);
double *GtypeGetDouble(Gtype *inp);
void GtypePrintDouble(Gtype *inp);

 double GtypeRank(Gtype *inp);
 double GtypeRankInt(Gtype *inp);
 double GtypeRankFloat(Gtype *inp);
 double GtypeRankDouble(Gtype *inp);

int GtypeCmp(Gtype *inp, Gtype *tp);
int GtypeAssign(Gtype *this, const Gtype *that);
int GtypeClone(Gtype* this, const Gtype* that);

int GtypeRefresh(Gtype *this);

#endif


#ifndef _GENV_H_
#define _GENV_H_ 


#define GERROR(mssg) do { \
  printf ("@ %s (%d): ", __FILE__, __LINE__); \
  printf (mssg); \
  exit(1); \
  } while (0)

#define GECHO(mssg) do { \
  printf (" %s \n", mssg);\
  fflush(stdout); \
  } while(0)

#endif

#    gethsemane project makefile
#         by Arash Ghasemi
# 
###############################################
VPATH = ./:../src:
%.o: %.c
	$(CC) $(CCOMPILEFLAGS) $^ -o $@ 
###############################################
###############################################
## NOTE!!! Now select your compiler from below 
CC = cc
#CC = pcc
# CC = icc
INCS    = ../inc
# IS_DEBUG = -DDEBUG_VERBOSE
# CCOMPILEFLAGS  =  -I$(INCS) -c -Wall -g -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition $(IS_DEBUG) 
CCOMPILEFLAGS  =  -I$(INCS) -c -O3 $(IS_DEBUG) 
LIBS    = 
# LINKFLAGS    = -L$(LIBS) -I$(INCS)
LINK_SUFFIX  = 
# LINK_SUFFIX  =     -llapack -lblas
# OMP_FLAGS = -fopenmp

## NOTE!!! Now add your object files that you need for 
#          your test case problem. 

### objects
OBJ1 = Gtype.o GtypeTest.o 
OBJ2 = Gtype.o Glist.o GlistTest.o
OBJ3 = Gtype.o Glist.o Gcart.o Greorder.o GreorderTest.o
###

### compile and link
EXE1 = GtypeTest.run 
EXE2 = GlistTest.run
EXE3 = GreorderTest.run

all: $(EXE1) $(EXE2) $(EXE3)
GtypeTest.run:  $(OBJ1)
	$(CC)  -o $@ $(LINKFLAGS) $(OBJ1) $(LINK_SUFFIX)
GlistTest.run:  $(OBJ2)
	$(CC)  -o $@ $(LINKFLAGS) $(OBJ2) $(LINK_SUFFIX)
GreorderTest.run:  $(OBJ3)
	$(CC)  -o $@ $(LINKFLAGS) $(OBJ3) $(LINK_SUFFIX)

clean:
	rm *.run *~ *# *.o

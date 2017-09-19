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
# CC = icc
INCS    = ../inc
CCOMPILEFLAGS  =  -I$(INCS) -c -Wall -g -O3 -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition 
LIBS    = 
LINKFLAGS    = -L$(LIBS) -I$(INCS)
LINK_SUFFIX  = 
# LINK_SUFFIX  =     -llapack -lblas
# OMP_FLAGS = -fopenmp

## NOTE!!! Now add your object files that you need for 
#          your test case problem. 

### objects
OBJ = Glist.o GlistTest.o  
###

### compile and link
EXE = exe.run

all: $(EXE)
exe.run:  $(OBJ)
	$(CC)  -o $@ $(LINKFLAGS) $(OBJ) $(LINK_SUFFIX)
clean:
	rm *.run *~ *# $(OBJ)

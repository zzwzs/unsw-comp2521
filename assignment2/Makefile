# Makefile for COMP2521 assignment2

CC=gcc
CFLAGS=-Wall -Werror -g
OBJS=pagerank.o readdata.o set.o graph.o
OBJS2=inverted.o BSTree.o set.o
OBJS3=searchPagerank.o
OBJS4=searchTfIdf.o]BINS=inverted pagerank searchPagerank searchTfIdf

all : $(BINS)

inverted: $(OBJS2)
   $(CC) -o inverted $(OBJS2)
   
pagerank : $(OBJS)
   $(CC) -o inverted $(OBJS)
   
searchPagerank : $(OBJS3)
   $(CC) -o searchPagerank $(OBJS3)
   
searchTfIdf : $(OBJS4)
   $(CC) -o searchTfIdf $(OBJS4)
   
   
inverted.o : inverted.c inverted.h
BSTree.o : BSTree.c BSTree.h
Pagerank.o : pagerank.c pagerank.h
readdata.o : readdata.c readdata.h
graph.o : graph.c graph.h
set.o : set.c set.h
searchTfIdf.o : searchTfIdf.c searchTfIdf.h

clean : 
      rm -f pagerank $(OBJS) core *.dSYM
      rm -f inverted $(OBJS2) core *.dSYM
      rm -f searchPagerank $(OBJS3) core *.dSYM
      rm -f searchTfIdf $(OBJS4) core *.dSYM
      rm -f scaledFootrule $(OBJS5) core *.dSYM

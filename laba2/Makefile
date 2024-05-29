CC=gcc
CFLAGS=-W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic

.PHONY: all run

all: parent child

parent: parent.o FunctionsParent.o
	$(CC) $(CFLAGS) -o parent parent.o FunctionsParent.o

child: child.o FunctionsChild.o FunctionsParent.o 
	$(CC) $(CFLAGS) -o child child.o FunctionsChild.o FunctionsParent.o

parent.o: parent.c FunctionsParent.h 
	$(CC) $(CFLAGS) -c -o parent.o parent.c

child.o: child.c FunctionsChild.h
	$(CC) $(CFLAGS) -c -o child.o child.c

FunctionsParent.o: FunctionsParent.c FunctionsParent.h
	$(CC) $(CFLAGS) -c -o FunctionsParent.o FunctionsParent.c

FunctionsChild.o: FunctionsChild.c FunctionsChild.h 
	$(CC) $(CFLAGS) -c -o FunctionsChild.o FunctionsChild.c

run:
	make child
	make parent
	CHILD_PATH=./child LC_COLLATE=C ./parent environ.txt



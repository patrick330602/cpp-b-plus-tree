CC=g++
ARGS=-std=c++11

all : bptree

bptree : BPlusTree.o Exceptions.o InternalNode.o LeafNode.o Node.o Printer.o Record.o main.o
	$(CC) $(ARGS) $^ -o $@
	rm *.o

BPlusTree.o	: BPlusTree.cpp BPlusTree.h Definitions.h
	$(CC) $(ARGS) -c $<

Exceptions.o : Exceptions.cpp Exceptions.h Definitions.h
	$(CC) $(ARGS) -c $<

InternalNode.o : InternalNode.cpp InternalNode.h Definitions.h
	$(CC) $(ARGS) -c $<

LeafNode.o : LeafNode.cpp LeafNode.h Definitions.h
	$(CC) $(ARGS) -c $<

Node.o : Node.cpp Node.h Definitions.h
	$(CC) $(ARGS) -c $<

Printer.o : Printer.cpp Printer.h Definitions.h
	$(CC) $(ARGS) -c $<

Record.o : Record.cpp Record.h Definitions.h
	$(CC) $(ARGS) -c $<

main.o : main.cpp Definitions.h 
	$(CC) $(ARGS) -c $<

clean :
	rm -f *.o bptree

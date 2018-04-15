CC=g++
ARGS=-std=c++11 -g

all : bptree

bptree : Tree.o InternalNode.o LeafNode.o Node.o Record.o main.o
	$(CC) $(ARGS) $^ -o $@

Tree.o: Tree.cpp Tree.h 
	$(CC) $(ARGS) -c $<

InternalNode.o: InternalNode.cpp InternalNode.h 
	$(CC) $(ARGS) -c $<

LeafNode.o: LeafNode.cpp LeafNode.h 
	$(CC) $(ARGS) -c $<

Node.o: Node.cpp Node.h 
	$(CC) $(ARGS) -c $<

Record.o: Record.cpp Record.h 
	$(CC) $(ARGS) -c $<

main.o: main.cpp  
	$(CC) $(ARGS) -c $<

clean :
	rm -f *.o bptree bptree.exe 

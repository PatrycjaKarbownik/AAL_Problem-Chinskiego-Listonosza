cc=g++

all: aal

aal: main.o Graph.o Generator.o
	$(cc) main.o Graph.o Generator.o -o aal

main.o: main.cpp Graph.h Generator.h
	$(cc) -c main.cpp

Graph.o: Graph.cpp Graph.h
	$(cc) -c Graph.cpp

Generator.o: Generator.cpp Generator.h Graph.h
	$(cc) -c Generator.cpp

clean:
	rm -rf *o aal

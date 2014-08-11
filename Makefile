all: simul

simul: simul.o main.o
	g++ simul.o main.o -o simul

simul.o: simul.cpp simul.h
	g++ -c simul.cpp

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -rf *.o

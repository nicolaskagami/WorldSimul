#Makefile Supports Both Windows (under mingw) and linux
SDL_LIB = -lSDL2main -lSDL2 
SYS := $(shell gcc -dumpmachine)
ifneq (, $(findstring linux, $(SYS)))
	LDFLAGS = $(SDL_LIB)
else ifneq(, $(findstring mingw, $(SYS)))
	LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
else
	echo "Unrecognized Option"
endif

all: simul

simul: main.o simul.o TextureManager.o Game.o
	g++ -o simul main.o TextureManager.o simul.o Game.o $(LDFLAGS) 
main.o: main.cpp
	g++ -c main.cpp
Game.o: Game.cpp
	g++ -c Game.cpp
TextureManager.o: TextureManager.cpp
	g++ -c TextureManager.cpp -lSDL2
simul.o: simul.cpp simul.h
	g++ -c simul.cpp

clean: 
	rm -rf *.o

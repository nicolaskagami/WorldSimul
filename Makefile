#Makefile Supports Both Windows (under mingw) and linux


SDL_LIB = -lSDL2main -lSDL2 
SYS := $(shell gcc -dumpmachine)

ifneq (,$(findstring linux, $(SYS)))
	#Linux
BINARIES=./bin/
SOURCE=./src/
INCLUDE=./include/
LDFLAGS = $(SDL_LIB)
$(info Compiling for Linux)
else ifneq (,$(findstring mingw, $(SYS)))
	#Windows MingW
BINARIES=.\\bin\\
SOURCE=.\\src\\
INCLUDE=.\\include\\
LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
$(info Compiling for Windows MingW)
else
	#Others
$(info OS not recognised)
all:
endif

all: $(BINARIES)simul

$(BINARIES)simul: $(BINARIES)main.o $(BINARIES)simul.o $(BINARIES)TextureManager.o $(BINARIES)Game.o
	g++ -o $(BINARIES)simul $(BINARIES)main.o $(BINARIES)TextureManager.o $(BINARIES)simul.o $(BINARIES)Game.o $(LDFLAGS) 
$(BINARIES)main.o: $(SOURCE)main.cpp
	g++ -c $(SOURCE)main.cpp -o $(BINARIES)main.o
$(BINARIES)Game.o: $(SOURCE)Game.cpp
	g++ -c $(SOURCE)Game.cpp -o $(BINARIES)Game.o
$(BINARIES)TextureManager.o: $(SOURCE)TextureManager.cpp
	g++ -c $(SOURCE)TextureManager.cpp -lSDL2 -o $(BINARIES)TextureManager.o
$(BINARIES)simul.o: $(SOURCE)simul.cpp $(INCLUDE)simul.h
	g++ -c $(SOURCE)simul.cpp -o $(BINARIES)simul.o

clean: 
	rm -rf $(BINARIES)*.o

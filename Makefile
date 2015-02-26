#Makefile Supports Both Windows (under mingw) and linux


BINARIES=./bin
SOURCE=./src
INCLUDE=./include

SDL_LIB = -lSDL2main -lSDL2 
SYS := $(shell gcc -dumpmachine)
ifneq (, $(findstring linux, $(SYS)))
	LDFLAGS = $(SDL_LIB)
else ifneq(, $(findstring mingw, $(SYS)))
	LDFLAGS = -lmingw32 -mwindows -mconsole $(SDL_LIB)
else
	echo "Unrecognized Option"
endif

all: $(BINARIES)/simul

$(BINARIES)/simul: $(BINARIES)/main.o $(BINARIES)/simul.o $(BINARIES)/TextureManager.o $(BINARIES)/Game.o
	g++ -o $(BINARIES)/simul $(BINARIES)/main.o $(BINARIES)/TextureManager.o $(BINARIES)/simul.o $(BINARIES)/Game.o $(LDFLAGS) 
$(BINARIES)/main.o: $(SOURCE)/main.cpp
	g++ -c $(SOURCE)/main.cpp
$(BINARIES)/Game.o: $(SOURCE)/Game.cpp
	g++ -c $(SOURCE)/Game.cpp
$(BINARIES)/TextureManager.o: $(SOURCE)/TextureManager.cpp
	g++ -c $(SOURCE)/TextureManager.cpp -lSDL2
$(BINARIES)/simul.o: $(SOURCE)/simul.cpp $(INCLUDE)/simul.h
	g++ -c $(SOURCE)/simul.cpp

clean: 
	rm -rf $(BINARIES)/*.o

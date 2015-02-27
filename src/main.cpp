#include<stdio.h>
#include<unistd.h>
#include"../include/simul.h"
#include"../include/SDL2/SDL.h"
#include"../include/Game.h"
#include"../include/TextureManager.h"

#define WINDOW_HEIGHT 640 
#define WINDOW_WIDTH 800 
#define WINDOW_TITLE "World Simulation"

Humanity demos;

int main(int argc, char* args[])
{
    
    TheGame.init(WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
 
    TheTextureManager.load("./Textures/B.bmp","Ground",TheGame.getRenderer());
    
    while(TheGame.isRunning())
    {    
        TheGame.render();
        TheGame.handleEvents();
        usleep(100);
    }
    
    TheGame.clean();
    
    return 0;

}

/*int main(int argc, char ** argv)
{
    Map mapa1(10,10);
    mapa1.RandomizeHeight(0);
    mapa1.print();
    mapa1.SmoothHeight();
    mapa1.print();

    demos.print();


}*/

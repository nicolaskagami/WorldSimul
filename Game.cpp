//Game object implementation. Handles the game loop.
#include "Game.h"

#include <stdlib.h>

#define TILE_HEIGHT 16
#define TILE_WIDTH 16

Map mapa(40,50);

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    // attempt to initialize SDL.
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        // init the window.
        ptWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        
        if(ptWindow != NULL)
        {
            ptRenderer = SDL_CreateRenderer(ptWindow,
                -1,
                SDL_RENDERER_ACCELERATED);
            if(ptRenderer != NULL)
            {
                SDL_SetRenderDrawColor(ptRenderer, 0, 0, 0, 255);
            }
            else
            {
                fprintf(stderr,"error: renderer init failed.\n");
                return false;
            }
        }
        else
        {
            fprintf(stderr,"error: window init failed.\n");
            return false;
        }
    }
    else
    {
        fprintf(stderr,"error: SDL init failed.\n");
        return false;
    }
    
    
    // set the game as running.   
    running = true;
    mapa.RandomizeHeight(2);
    mapa.SmoothHeight();
    mapa.Rain(100);
    return true;
}

void Game::render()
{
    // clear to rendering color.
    SDL_RenderClear(ptRenderer);
    mapa.Rain(1);
    mapa.Runoff();
    for(int i = 0; i < mapa.height;i++)
    {
        for(int j = 0; j< mapa.width;j++)
        {
            TheTextureManager.draw("Ground",16*j,16*i,(mapa.map[i*mapa.width+j].height / 32 )*16,16,16,16,ptRenderer);
        }

    }
    for(int i = 0; i < mapa.height;i++)
    {
        for(int j = 0; j< mapa.width;j++)
        {
            TheTextureManager.draw("Ground",16*j+4,16*i+4,(mapa.map[i*mapa.width+j].water / 32 )*16,32,8,8,ptRenderer);
        }

    }
    //TheTextureManager.draw("Ground",0,0,0,0,32,32,ptRenderer);
    //TheTextureManager.draw("Ground",0,32,0,32,32,32,ptRenderer);
    //TheTextureManager.draw("Ground",32,0,32,0,32,32,ptRenderer);
    
    // draw to the screen.
    SDL_RenderPresent(ptRenderer);
}

void Game::update()
{
   // Nothing for now.
}

void Game::handleEvents()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
        }
    }
}

void Game::clean()
{

    SDL_DestroyWindow(ptWindow);
    SDL_DestroyRenderer(ptRenderer);
    SDL_Quit();
}






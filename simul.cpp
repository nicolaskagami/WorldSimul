//Simulator version 0.1
//Author: Nicolas Silveira Kagami
//Bruno esteve aqui

#include"simul.h"
/*
    Ideas
    
Attributes:
    Height
    Water
    Hardness (1/absorption)
    Absorption dependant on plants?
    Stillness (calculated through the difference in water levels) Problem: river is not still, but the water level is constant
    

Goals:
    Mountains
        Generated out of high places in the mesh which are smoothed down due to the runoff
    Plains
        Generated out of faults which get leveled due to buildup
    Rivers
        Generated out of faults which lead the water to another place
    Lakes
        Generated out of low places that have saturated absorption

Processes:
    Rain
    Runoff
    Buildup
    Wind and clouds?

*/

void Tile::print()
{
    printf("Height: %.3d \t",height);
    printf("Water: %.3d \t",water);
    printf("Hardness: %.3d \t",hardness);
    printf("Absorption Rate: %.3d \n",absorption_rate);
}
Map::Map(int x, int y)
{
    printf("Creating Map %dx%d\n",x,y);
    map = (Tile *) malloc(x*y*sizeof(Tile));
    if(map == NULL)
    {
        printf("Map Creation: Malloc failed\n");
        exit(0);
    }
    height = x;
    width = y;

}
Map::~Map()
{
    free(map);
}
int Map::RandomizeHeight(int seed)
{
    printf("Randomizing Height\n");
    if(map)
    {
        srand(seed);
        int i;
        for(i=0;i<height*width;i++)
        {
            map[i].height = (unsigned char) rand();
            map[i].hardness = (unsigned char) rand();
            if( map[i].hardness == 0)
                map[i].hardness = 1;
            map[i].absorption_rate = (unsigned char) ABSORPTION_COEF * (int) rand()/map[i].hardness;
        }
        return 0;
    }
    else
    {
        return -1;
    }
}
int Map::SmoothHeight()
{
    printf("Smoothing Height\n");
    int * buffer;
    int i;
    buffer = (int*) malloc(height*width*4);
    for(i=0;i<height*width;i++)
    {
        int coupling = 0;
        buffer[i] = (int) SMOOTH_COEF*map[i].height;
        if(i%width != 0)
        {
            buffer[i]+= (int) map[i-1].height;
            coupling++;
        }
        if(i%width != width-1) 
        {
            buffer[i]+= (int) map[i+1].height;
            coupling++;
        }
        if(i/width != 0)
        {
            buffer[i]+= (int) map[i-width].height;
            coupling++;
        }
        if(i/width != height-1)
        {
            buffer[i]+= (int) map[i+width].height;
            coupling++;
        }
        buffer[i]/= (int) (SMOOTH_COEF+coupling);
        //printf("OLD: %.3d, Coup:%d, New: %.3d\n",map[i].height,coupling,buffer[i]);
    }
    for(i=0;i<height*width;i++)
        map[i].height = (unsigned char) buffer[i];
    free(buffer);
    return 0;
}
int Map::Rain(int intensity)
{
    printf("Raining\n");
    if(map)
    {
        int i;
        unsigned char rain;
        for(i=0;i<height*width;i++)
        {
            rain = (unsigned char) intensity*(map[i].height);
            if(rain + map[i].water > 255)
                map[i].water=255;
            else
                map[i].water+=rain;
        }
        return 0;
    }
    else
    {
        return -1;
    }
}
int Map::Runoff()
{
    int * buffer;
    int i;
    buffer = (int*) malloc(height*width*4);
    for(i=0;i<height*width;i++)
    {
        int coupling = 0;
        int water_level = (int) RUNOFF_COEF*((int)map[i].height + (int)map[i].water);
        buffer[i] = water_level; 
        unsigned char absorbed;
        unsigned char runoff;
        unsigned char aux;
        int local_wl;
        if(i%width != 0)
        {
            local_wl= (int) map[i-1].height + (int) map[i-1].water;
            buffer[i]+= ((local_wl - water_level)/(1+local_wl+water_level))*map[i-1].water;
            coupling++;
        }
        if(i%width != width-1) 
        {
            local_wl= (int) map[i+1].height + (int) map[i+1].water;
            buffer[i]+= ((local_wl - water_level)/(1+local_wl+water_level))*map[i-1].water;
            coupling++;
        }
        if(i/width != 0)
        {
            local_wl= (int) map[i-width].height + (int) map[i-width].water;
            buffer[i]+= ((local_wl - water_level)/(local_wl+water_level+1))*map[i-1].water;
            coupling++;
        }
        if(i/width != height-1)
        {
            local_wl= (int) map[i+width].height + (int) map[i+width].water;
            buffer[i]+= ((local_wl - water_level)/(local_wl+water_level+1))*map[i-1].water;
            coupling++;
        }
        buffer[i]/= (int) (RUNOFF_COEF+coupling);
        absorbed = (buffer[i]*(int)map[i].absorption_rate)/256;
        buffer[i]-= absorbed;
        runoff = map[i].water - buffer[i]; 
        //map[i].height+= (unsigned char) ((int)((int)(255-map[i].height)*(absorbed - runoff))*(255 -(int)map[i].hardness))/BUILDOFF_COEF;
        //printf("Runoff: %d, Absorbed: %d\n",runoff, absorbed);
        //printf("Height: %.3d\t",map[i].height);
        //map[i].height+= (unsigned char) (((absorbed - runoff))/((map[i].height)*(map[i].hardness)));
        if(runoff > absorbed)
        {
            if(map[i].hardness == 0)
                map[i].hardness = 1;
            aux =(unsigned char) map[i].height - ((int)(runoff - absorbed))/map[i].hardness;
            printf("runoff: %.3d, absorbed: %.3d, hardness: %.3d\n",runoff, absorbed,map[i].hardness);
            printf("heigth: %.3d, aux: %.3d\n",map[i].height,aux);
            if(aux<=map[i].height)
                map[i].height = aux;
            else
                printf("wtf\n");
        }
        else
        {
            if(map[i].hardness == 0)
                map[i].hardness = 1;
            aux = map[i].height + ((absorbed - runoff)/(map[i].hardness));
            if(aux>=map[i].height)
                map[i].height = aux;
        }
        //printf("Height: %.3d\n",map[i].height);
        //map[i].hardness+= (unsigned char) ((255-map[i].hardness)*(runoff-absorbed))/256;
        //map[i].absorption_rate+= (unsigned char) ((255-map[i].absorption_rate)*((absorbed-runoff))/256);
        //map[i].print();
        //printf("\n");
    }
    for(i=0;i<height*width;i++)
        map[i].water = (unsigned char)buffer[i];
    free(buffer);
    return 0;
}
void Map::print()
{
    int x,y;
    printf("Map:\n");
    for(x=0;x<height;x++)
    {
        for(y=0;y<width;y++)
        {
            printf(" %.3d", map[x*height+y].height);
        }
        printf("\n");
    }
}
Human::Human(int identification)
{
    id = identification;
    age = 15 + rand() % 10;
    sex = rand()%2;
    happiness = 128;
    health = 255;
    nourishment = 128;
}
Human::~Human()
{
}
void Human::print()
{
    printf("ID: %d, Sex: %d, Age: %d, Happiness: %d, Nourishment: %d, Health: %d\n",id, sex, age, happiness, nourishment, health);
}
Humanity::Humanity()
{
    int i;
    humanity.reserve(INITIAL_POPULATION);
    for(i=0;i<INITIAL_POPULATION;i++)
    {
        humanity.push_back(Human(i));
    }
}
void Humanity::print()
{
    int i;
    printf("SIZE: %d\n",humanity.size());
    for(i=0;i < humanity.size();i++)
    {
        humanity[i].print();
    }
}

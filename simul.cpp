//Simulator version 0.1
//Author: Nicolas Silveira Kagami

#include"simul.h"

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
            map[i].height = (unsigned char) rand();
            map[i].hardness = (unsigned char) rand();
            map[i].absorption_rate = (unsigned char) ABSORPTION_COEF * rand()/map[i].hardness;
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
        for(i=0;i<height*width;i++)
            map[i].water = intensity*map[i].height + (unsigned char) rand();
        return 0;
    }
    else
    {
        return -1;
    }
}
int Map::Runoff()
{
    printf("Runoff\n");
    int * buffer;
    int i;
    buffer = (int*) malloc(height*width*4);
    for(i=0;i<height*width;i++)
    {
        int coupling = 0;
        buffer[i] = (int) RUNOFF_COEF*map[i].height + map[i].water;
        if(i%width != 0)
        {
            buffer[i]+= (int) map[i-1].height + map[i-1].water;
            coupling++;
        }
        if(i%width != width-1) 
        {
            buffer[i]+= (int) map[i+1].height + map[i+1].water;
            coupling++;
        }
        if(i/width != 0)
        {
            buffer[i]+= (int) map[i-width].height + map[i-width].water;
            coupling++;
        }
        if(i/width != height-1)
        {
            buffer[i]+= (int) map[i+width].height + map[i+width].water;
            coupling++;
        }
        buffer[i]/= (int) (RUNOFF_COEF+coupling);
        buffer[i]-= (int) (map[i].water*map[i].absorption_rate)/256;
        map[i].height+= (unsigned char) BUILDOFF_COEF*(buffer[i] - map[i].water);
        //printf("OLD: %.3d, Coup:%d, New: %.3d\n",map[i].height,coupling,buffer[i]);
    }
    for(i=0;i<height*width;i++)
        map[i].water = (unsigned char) buffer[i] - map[i].height;
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

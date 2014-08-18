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
        return 0;
    }
    else
    {
        return -1;
    }
}
int Map::SmoothHeight()
{
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
int Map::Runoff()
{
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

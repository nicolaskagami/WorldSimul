//Simulator version 0.1
//Author: Nicolas Silveira Kagami

#include<stdlib.h>
#include<stdio.h>

#define MAX_RES_PER_TILE 4
#define SMOOTH_COEF 4

class Tile
{
    public:
        int resource[MAX_RES_PER_TILE];
        unsigned char quantity[MAX_RES_PER_TILE];
        unsigned char height;
        //add nutrients, humidity, erosion
};
class Map
{
    private:
        Tile * map;
        int height,width;
    public:
        Map(int x, int y);
        int RandomizeHeight(int seed);
        int SmoothHeight();
        ~Map();
        void print();

};
class Path
{
};
class Being
{
};

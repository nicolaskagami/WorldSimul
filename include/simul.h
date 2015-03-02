#ifndef WORLD_SIMUL_H
#define WORLD_SIMUL_H
//Simulator version 0.1
//Author: Nicolas Silveira Kagami

#include<stdlib.h>
#include<stdio.h>
#include<vector>

//Geo
#define PLATE_COEF 5
#define PLATE_MAX 4 
#define SMOOTH_COEF 1 
#define PRECIPITATION_HEIGHT_COEF 0.5 //How much precipitation per height
#define WATER_HEIGHT_COEF 0.5 //How high the water can be to overflow
#define ABSORPTION_COEF 1
#define RUNOFF_COEF 1
#define BUILDOFF_COEF 10

class Tile
{
    public:
        //int resource[MAX_RES_PER_TILE];
        //unsigned char quantity[MAX_RES_PER_TILE];
        unsigned char height;
        unsigned char plate;
        unsigned char water;
        unsigned char hardness;
        unsigned char absorption_rate;
        //add nutrients, humidity, erosion
        void print();
};
class Map
{
    public:
        Tile * map;
        int height,width;
        Map(int x, int y);
        int RandomizeHeight(int seed);
        int SmoothHeight();
        int RandomizePlate(int seed);
        int SmoothPlate();
        int AggregatePlates();
        int Rain(int intensity);
        int Runoff(); 
        ~Map();
        void print();

};
class Path
{
};
class ResourceInfo
{
    public:
        unsigned char cost;
        unsigned char availability;
        int x;
        int y;
        int responsible;
};
#endif

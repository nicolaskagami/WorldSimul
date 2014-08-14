//Simulator version 0.1
//Author: Nicolas Silveira Kagami

#include<stdlib.h>
#include<stdio.h>
#include<vector>

#define INITIAL_POPULATION 256
#define MAX_RES_PER_TILE 4
#define MAX_HUMANS 1024
#define MAX_FRIENDS 8
#define MAX_FOES 8
#define SMOOTH_COEF 1 


//Have a knowledge of places where resources can be found, groups/people responsible


class Tile
{
    public:
        //int resource[MAX_RES_PER_TILE];
        //unsigned char quantity[MAX_RES_PER_TILE];
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
class ResourceInfo
{
    public:
        unsigned char cost;
        unsigned char availability;
        int x;
        int y;
        int responsible;
};
class Human 
{
    public:
        int id;
        unsigned char sex;
        unsigned char age;
        int friends[MAX_FRIENDS];
        unsigned char friends_intensity[MAX_FRIENDS];
        int foes[MAX_FOES];
        unsigned char foes_intensity[MAX_FOES];
        unsigned char happiness;
        unsigned char nourishment;
        unsigned char health;

        Human(int identification);
        ~Human();
        void print();
};
class Humanity
{
    public:
        std::vector<Human> humanity;
        Humanity();
        void print();
};

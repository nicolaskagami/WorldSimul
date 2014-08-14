#include<stdio.h>
#include"simul.h"

Humanity demos;
int main(int argc, char ** argv)
{
    Map mapa1(10,10);
    mapa1.RandomizeHeight(0);
    mapa1.print();
    mapa1.SmoothHeight();
    mapa1.print();



}

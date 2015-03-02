//Simulator version 0.1
//Author: Nicolas Silveira Kagami

#include"../include/humanity.h"

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

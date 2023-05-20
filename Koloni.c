//
// Created by BERKE on 16.05.2023.
//
#include "Koloni.h"
#include <stdlib.h>

Colony createColony(char symbol,int population,int food_stock,int wins,int loses,int is_death)
{
    Colony this;
    this = (Colony) malloc(sizeof(struct COLONY));
    this->symbol = symbol;
    this->population = population;
    this->food_stock = food_stock;
    this->wins = wins;
    this->loses = loses;
    this->destroy = &destroyColony;
    this->is_death = is_death;
    return this;
}


void destroyColony(const Colony this)
{
    if(this == NULL)
        return;
    this->destroy(this);
    free(this);
}
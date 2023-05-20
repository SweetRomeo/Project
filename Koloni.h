//
// Created by BERKE on 11.05.2023.
//

#ifndef KOLONI_H
#define KOLONI_H

struct COLONY{
    char symbol;
    int population;
    int food_stock;
    int wins;
    int loses;
    int is_death;
    void (*destroy)(struct COLONY*);
};

typedef struct COLONY*Colony;

Colony createColony(char,int,int,int,int,int);
void destroyColony(Colony);



#endif //KOLONI_H

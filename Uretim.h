//
// Created by BERKE on 16.05.2023.
//

#ifndef UNTITLED2_URETIM_H
#define UNTITLED2_URETIM_H


struct GENERATE_COLONY{
    char symbol;
    int population;
    int food_stock;
    int wins;
    int loses;
    int is_death;
    char* creationDate;
    void (*setColony)();
    char* (*getCreationDate)(struct GENERATE_COLONY*);
    void (*destroyColony)(struct GENERATE_COLONY*);
    void(*setSymbol)(struct GENERATE_COLONY*,char*);
    char*(*toString)(struct GENERATE_COLONY*,void*);

};

typedef struct GENERATE_COLONY* GenerateColony;

char* getTime();
int mystrlen(char* str);
int Length(double value);
GenerateColony setColony(char symbol);
void setSymbol(GenerateColony this,char symbol);
char* getCreationDate(GenerateColony this);
char* toString(struct GENERATE_COLONY*,void*);
void destroy_colony(GenerateColony this);


#endif //UNTITLED2_URETIM_H

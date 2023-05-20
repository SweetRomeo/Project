//
// Created by BERKE on 16.05.2023.
//
#include "Uretim.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

char* getTime()
{
    char*str = malloc(sizeof(char) * 100);
    time_t now = time(NULL);
    strftime(str,100,"%d %m %H:%M %Y", localtime(&now));
    return str;
}
int mystrlen(char* str)
{
    int len = 0;
    while(*str != '\0'){
        len++;
        str++;
    }
    return len;
}


int Length(double value)
{
    char str[50];
    sprintf(str,"%lf",value);
    int len = mystrlen(str);
    return len;
}

GenerateColony setColony(char symbol)
{
    GenerateColony this;
    this = (GenerateColony) malloc(sizeof(struct GENERATE_COLONY));
    this->creationDate = getTime();
    this->symbol = symbol;
    this->getCreationDate = &getCreationDate;
    this->toString = &toString;
    this->destroyColony = &destroy_colony;
    return this;
}

void setSymbol(const GenerateColony this,char symbol)
{
    this->symbol = symbol;
}

char* getCreationDate(const GenerateColony this)
{
    return this->creationDate;
}

char* toString(struct GENERATE_COLONY*this,void* p)
{
    int total_length = 36;
    total_length += Length(this->symbol);
    total_length += Length(this->population);
    total_length += Length(this->food_stock);
    total_length += Length(this->wins);
    total_length += Length(this->loses);
    char*str = (char*) malloc(sizeof(char) * total_length + 1);
    sprintf(str,"   %c     %d      %d      %d      %d",this->symbol,this->population,this->food_stock,this->wins,this->loses);
    return str;
}

void destroy_colony(const GenerateColony this)
{
    if(this == NULL)
        return;
    free(this-> creationDate);
    free(this);
}

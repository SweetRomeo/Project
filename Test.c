#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "Oyun.h"
#include "Taktik.h"
#include "Koloni.h"
#include "Uretim.h"
#define randomize() srand(time(NULL))
#define SIZE 100

void readStandardInputBuffer(char*str,char ch,int*string_size,int*space_char,int*last_space_temp)
{
    while ((ch = getchar()) != '\n' && (*string_size < SIZE-1)) {
        str[*string_size] = ch;
        if (ch == '\b') {
            printf("\b \b");
            --*string_size;
            if (*last_space_temp)
                --*space_char;
        } else {
            ++*string_size;
            printf("%c", ch);
            if (ch == ' ') {
                ++*space_char;
                *last_space_temp = 1;
            } else {
                *last_space_temp = 0;
            }
        }
    }
}
int powerOfTenPositive(int num) {
    int res = 1;
    int i;
    for(i = 0; i < num; i++)
        res *= 10;
    return res;
}


int* dataUnPacker(const char* stringData, int space_char) {
    int temp = 0;
    int stringIndex = 0;
    int *numData = (int *)malloc(space_char * sizeof(int));
    int i;
    for(i = 0; i < space_char; i++)
        numData[i] = 0;
    space_char = 0;
    while(stringData[stringIndex] != '\0') {
        while(stringData[stringIndex] != ' ') {
            stringIndex++;
            temp++;
        }
        for(i = temp-1; i >= 0; i--) {
            numData[space_char] += powerOfTenPositive(i)*(stringData[stringIndex - i - 1] - '0');
        }
        space_char++;
        stringIndex++;
        temp = 0;
    }


    return numData;

}

int main() {
    char str[SIZE];
    char ch = 0;
    int string_size = 0;
    int space_char = 0, last_space_temp = 0;
    readStandardInputBuffer(str,ch,&string_size,&space_char,&last_space_temp);
    str[string_size] = ' ';
    str[string_size + 1] = '\0';
    printf("\n");
    printf("Input string: %s\n", str);
    printf("Number of spaces: %d\n", space_char);
    int number_of_colonies = ++space_char;
    Colony* colonies = (Colony *) malloc(sizeof(Colony) * number_of_colonies);
    int* num_data_res = dataUnPacker(str, number_of_colonies);
    for(int i = 0;i < number_of_colonies;++i)
        createColonyTest(&colonies[i],num_data_res);
    int death_count = 0;
    int turn_count = 1;
    while(1) {
        printf("----------------------------------------------------------------------------\n");
        printf("Tur Sayisi: %d\n", turn_count);
        printf("Koloni    Popilasyon   Yemek Stogu     Kazanma    Kaybetme\n");
        turn_count++;
        for(int i = 0; i < space_char; i++) {
            if(!colonies[i]->is_death&&(colonies[i]->population <= 0||colonies[i]->food_stock <= 0)) {
                death_count++;
                colonies[i]->is_death = 1;
                printf("%d oldu.\n", i);
            }
            if(!colonies[i]->is_death)
                printf("%4c %8d %13d %13d %13d\n", colonies[i]->symbol, colonies[i]->population, colonies[i]->food_stock, colonies[i]->wins, colonies[i]->loses);
            else
                printf("%4c      --         --         --        --\n", colonies[i]->symbol);

        }
        printf("----------------------------------------------------------------------------\n");

        for(int i = 0; i < space_char-1; i++)
            for(int j = i + 1; j < space_char; j++) {
                if(!(colonies[i]->is_death||colonies[j]->is_death)) {
                    int temp_savas_1 = Savas(); //i kolonisi
                    int temp_savas_2 = Savas(); //j kolonisi22
                    int kazanan;
                    int foodtransfertemp;

                    if(temp_savas_1 == temp_savas_2) {
                        if(colonies[i]->population == colonies[j]->population)
                            kazanan = rand()%2+1;
                        else if (colonies[i]->population > colonies[j]->population)
                            kazanan = 1;
                        else
                            kazanan = 2;

                    } else if(temp_savas_1 > temp_savas_2) {
                        kazanan = 1;
                    } else {
                        kazanan = 2;
                    }

                    if(kazanan == 1) {
                        colonies[i]->wins++;
                        colonies[j]->loses++;
                        colonies[j]->population -= colonies[j]->population*((int)((double)(temp_savas_1 - temp_savas_2)/1000));
                        foodtransfertemp = (int)(((double)colonies[j]->food_stock/100)*10);
                        colonies[i]->food_stock += foodtransfertemp;
                        colonies[j]->food_stock -= foodtransfertemp;

                    }
                    else {
                        colonies[i]->loses++;
                        colonies[j]->wins++;
                        colonies[i]->population -= colonies[i]->population*((int)((double)(temp_savas_2 - temp_savas_1)/1000));
                        foodtransfertemp = (int)(((double)colonies[i]->food_stock/100)*10);
                        colonies[j]->food_stock += foodtransfertemp;
                        colonies[i]->food_stock -= foodtransfertemp;

                    }
                }
            }
        for(int i = 0; i < space_char; i++) {
            colonies[i]->population += (int)(((double)colonies[i]->population/100)*20);
            colonies[i]->food_stock -= colonies[i]->population*2;
        }
        if(death_count >= space_char-1)
            break;
        printf("Savasi devam ettirmek icin tiklayiniz... \n");
        while (!getchar());
    }
    free(colonies);
    return 0;
}







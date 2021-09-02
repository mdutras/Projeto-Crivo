// 10.000.000
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "tools.h"

void crivo(int inicio, int fim, short* n)
{
    int mult[] = {2, 3, 5,7};
    int counter = 4;
    for(int i = 1; counter > 0; i++){
        for(int j = 0; j < counter; j++){
            if((mult[j] + i * mult[j]) > fim){
                counter--;
            }else{
                if(n[(mult[j] + i * mult[j]) - 1]){
                    n[(mult[j] + i * mult[j]) - 1] = 0;
                }
            }
        }
    }
}


int main()
{
    int NUM_ELEMS;
    printf("Insira o valor máximo do intervalo: ");
    scanf("%d", &NUM_ELEMS);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    short *b = (short *) malloc(sizeof(short) * NUM_ELEMS);
    for(int i = 0; i <= NUM_ELEMS; i++){
        b[i] = 1; 
    }
    crivo(1, NUM_ELEMS, b);
    int prime_counter = 0;
    for (int i = 0, j = 1; i < NUM_ELEMS; i++)
    {
        if (b[i])
        {
            cyan(i + 1, tam(NUM_ELEMS));
            prime_counter++;
            j++;
        }
        if (j > 10)
        {
            printf("\n");
            j = 1;
        }
    }
    printf("\n");
    free(b);
    printf("Há %d primos entre 1 e %d\n", prime_counter, NUM_ELEMS);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    float delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    printf("O programa demorou %.2f milissegundos\n", delta_us);
    return 0;
}
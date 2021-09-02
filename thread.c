//gcc -fopenmp -o thread thread.c tools.c

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include "tools.h"

#define NUM_THREADS 4

void crivo(int inicio, int fim, int num,short* n)
{
    #pragma omp parallel num_threads(NUM_THREADS)
    for(int j = 2; num * j <= fim; j++){
        n[(num * j) - 1] = 0;
    }

}

int main(){
    int NUM_ELEMS;
    printf("Insira o valor máximo do intervalo: ");
    scanf("%d", &NUM_ELEMS);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    short *nums = (short*) malloc(sizeof(short) * NUM_ELEMS);
    for(int i = 0; i <= NUM_ELEMS; i++){
        nums[i] = 1; 
    }
    int mult[] = {2,3,5,7}; 
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        crivo(1, NUM_ELEMS, mult[omp_get_thread_num()], nums);
    }
    int prime_counter = 0;
    for (int i = 0, j = 1; i < NUM_ELEMS; i++)
    {
        if (nums[i])
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
    free(nums);
    printf("Há %d primos entre 1 e %d\n", prime_counter, NUM_ELEMS);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    float delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
    printf("O programa demorou %.2f milissegundos\n", delta_us);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <mpi.h>
#include "tools.h"

#define NUM_ELEMS 10000000

int main(int argc, char **argv) 
{  
    short *b = (short *) malloc(sizeof(short) * NUM_ELEMS);
    for(int i = 0; i < NUM_ELEMS; i++){
        b[i] = 1; 
    }
    double inicio, fim;
    int rank, counter = 2;
    struct timespec start, end;
    int mult[2][2] = {{2, 3}, {5, 7}};

    MPI_Init(NULL, NULL);
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    for(int i = 1; counter > 0; i++){
        for(int j = 0; j < counter; j++){
            // printf("rank %d b[%d]\n", rank, (mult[rank][0] + i * mult[rank][0]) - 1);
            if((mult[rank][j] + i * mult[rank][j]) > NUM_ELEMS){
                counter--;
            }else{
                if(b[(mult[rank][j] + i * mult[rank][j]) - 1]){
                    b[(mult[rank][j] + i * mult[rank][j]) - 1] = 0;
                }
            }
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0){
        MPI_Send(b, NUM_ELEMS, MPI_SHORT, 1, 0, MPI_COMM_WORLD);
    }else{
        int prime_counter = 0, jump_counter = 1;
        short *n = (short *) malloc(sizeof(short) * NUM_ELEMS);
        MPI_Recv(n, NUM_ELEMS, MPI_SHORT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int i = 0; i < NUM_ELEMS; i++){
            if(b[i] + n[i] == 2 ){
                cyan(i + 1, tam(NUM_ELEMS));
                prime_counter++;
                jump_counter++;
            }
            if(jump_counter > 10){
                printf("\n");
                jump_counter = 1;
            }
        }
        free(n);
        printf("\n");
        printf("Há %d primos entre 1 e %d\n", prime_counter, NUM_ELEMS);
        fim = MPI_Wtime();
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        float delta_us = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
        printf("O programa demorou %.3f milissegundos\n", delta_us);
    }
    free(b);
    MPI_Finalize();
    
    return 0;
}
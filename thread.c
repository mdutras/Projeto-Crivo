#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include "tools.h"

#define NUM_ELEMS 100
#define NUM_THREADS 4

void crivo(int inicio, int fim, int *n){
    int multiples[] = {2,3,5,7};
    #pragma omp parallel for
    for(int i = 0; i < (fim - inicio) ; i++){
        n[i + inicio] = 1;
        #pragma omp parallel for
        for(int j = 0; j < 4; j++){
            if(((inicio + i) != multiples[j]) & ((inicio + i) % multiples[j] == 0)){
                n[i + inicio] = 0;
            }
        }
    }

}

int main(){
    int *nums = (int*) malloc(sizeof(int) * NUM_ELEMS);
    for(int i  = 0; i < NUM_ELEMS ; i++){
        nums[i] = 0;
    }
    int fraction = abs(NUM_ELEMS/NUM_THREADS);
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int inicio = (omp_get_thread_num() == 0 ? 1 : fraction * omp_get_thread_num());
        int fim = (omp_get_thread_num() == NUM_THREADS - 1 ? NUM_ELEMS + 1 : fraction * (omp_get_thread_num() + 1));
        printf("fim (%d) - inicio (%d) = %d\n", fim, inicio, fim - inicio);
        crivo(inicio, fim, nums);
    }
    int size = tam(NUM_ELEMS);
    for(int i  = 1; i <= NUM_ELEMS ; i++){
        if(nums[i]){
            green(i, size);
        }else{
            red(i, size);
        }
        if(i % 10 == 0){
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}
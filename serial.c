#include<stdio.h>
#include<stdlib.h>
#include "tools.h"

#define NUM_ELEMS 200

void crivo(int inicio, int fim, int *n){
    int multiples[] = {2,3,5,7};
    for(int i = 0; i < (fim - inicio) ; i++){
        n[i] = 1;
        for(int j = 0; j < 4; j++){
            if(((inicio + i) != multiples[j]) & ((inicio + i) % multiples[j] == 0)){
                n[i] = 0;
            }
        }
    }
}

int main(){
    int *b = (int*) malloc(sizeof(int) * NUM_ELEMS);
    crivo(1, NUM_ELEMS, b);
    int size = tam(NUM_ELEMS);
    for(int i = 0; i <= NUM_ELEMS ; i++){
        if(b[i]){
            green(i+1, size);
        }else{
            red(i+1, size);
        }
        if((i + 1) % 10 == 0){
            printf("\n");
        }
    }
    printf("\n");
    return 0;

}
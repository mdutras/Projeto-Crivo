#include<stdio.h>
#include<stdlib.h>
#include "tools.h"

void spaces(int num){
    for(int i = 0; i < num; i++){
        printf(" ");
    }
}

int tam(int num){
    int size = 0;
    for(float tam = num; tam >= 1;size++){
        tam = tam / 10;
    }
    return size;
}

void red(int c, int num){
    spaces(num - tam(c));
    printf("\033[0;31m");
    printf("%d ", c); 
    printf("\033[0m");
}

void green(int c, int num){
    spaces(num - tam(c));
    printf("\033[0;32m");
    printf("%d ", c); 
    printf("\033[0m");
}

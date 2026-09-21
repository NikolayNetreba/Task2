#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <string.h>

int add(int a, int b){
    return a + b;
}

int comp_int(const void* a, const void* b){
    double arg1 = *(double*)a;
    int arg2 = *(double*)b;

    if(arg1 > arg2) return 1;
    if(arg1 < arg2) return -1;
    return 0;
}


void check(void* arr, size_t size, int(*comp)(const void*, const void*)){
    char* bit = (char*)arr;

    printf("%d", comp(bit, bit + size));

}

void swap_elem(void* a, void* b, size_t size){
    char* arg1 = (char*)a;
    char* arg2 = (char*)b;
    char buff[size];

    memcpy(buff, a, size);
    memcpy(a, b, size);
    memcpy(b, buff, size);
}

typedef struct{
    int a;
    int* c;
} te;

void p(te* arg){
    arg->c = (int*)calloc(3, sizeof(int));
    arg->c[0] = 10;
    printf("%d", arg->c[0]);
}

int main(){
    printf("%d", 'A');

}

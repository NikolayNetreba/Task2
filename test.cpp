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

int main(){
    double arr[] = {1.2, 3.5};

    swap_elem(&arr[0], &arr[1], sizeof(double));

    printf("%lf, %lf", arr[0], arr[1]);
}

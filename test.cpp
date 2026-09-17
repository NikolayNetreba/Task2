#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

int add(int a, int b){
    return a + b;
}

int comp_int(const void* a, const void* b){
    int arg1 = *(int*)a;
    int arg2 = *(int*)b;

    if(arg1 > arg2) return 1;
    if(arg1 < arg2) return -1;
    return 0;
}


void check(void* arr, size_t size, int(*comp)(const void*, const void*)){
    char* bit = (char*)arr;

    printf("%d", comp(bit, bit + size));

}

int main(){
//     int (*ptr)(int, int) = add;
//     int result = ptr(1, 2);
//
//     int a = 0;
//     void* p = &a;
//     scanf("%d", (int*)p);
//     printf("%    d", *(int*)p);
    int arr[] = {9, -2};
    check(arr, sizeof(int), comp_int);

}

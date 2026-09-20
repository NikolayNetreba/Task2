#include <cstddef>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "colors.h"

const double EPS = 1e9;

void printArr(void* arr, char* L, char* R, char* pivot, size_t len, size_t size){
    char* mass = (char*)arr;

    printf("pivot = %d\n", *pivot);
    for(char* i = mass; i < mass + len * size; i += size){
        if(i <= L){
            printf("| " MAKE_BLUE("%3s") " | ", *(int*)i);
        } else if(i == pivot) {
            printf("| " MAKE_YELLOW("%3s") " | ", *(int*)i);
        } else if(i >= R){
            printf("| " MAKE_RED("%3s") " | ", *(int*)i);
        } else {
            printf("| %3s | ", *(int*)i);
        }
    }

    printf("\n");
    for(int i = 0; i < len; i++){
        printf("| %3d | ", i);
    }

    //for sleep print
    //getchar();

    printf("\n----------------------\n");
}

void swap_elem(void* a, void* b, size_t size){
    char* arg1 = (char*)a;
    char* arg2 = (char*)b;
    char buff[size];

    memcpy(buff, a, size);
    memcpy(a, b, size);
    memcpy(b, buff, size);
}

//len - length of array, size - size of array element (byte)
size_t partition(void* arr, size_t len, size_t size, int(*comp)(const void*, const void*)){
    assert(arr);

    char* start = (char*)arr;
    char* left = start - size, *right = start + len * size;

    size_t pivotIdx = (len - 1) / 2;
    char* pivot = (char*)malloc(size);
    memcpy(pivot, start + pivotIdx * size, size);

    while(1){
        do{
            left += size;
            //printArr(arr, left, right, pivot, len, size);
        } while(comp(left, pivot) < 0); //left < pivot

        do{
            right -= size;
            //printArr(arr, left, right, pivot, len, size);
        } while(comp(right, pivot) > 0); // right > pivot

        if(left >= right){
            free(pivot);
            return (right - start) / size; //pivot idx
        }
        swap_elem(left, right, size);
        //printArr(arr, left, right, pivot, len, size);
    }
}

void u_quick_sort(void* arr, size_t len, size_t size, int(*comp)(const void*, const void*)){
    assert(arr);
    assert(len >= 0);

    if(len < 2) return;

    size_t pivotIdx = partition(arr, len, size, comp);

    u_quick_sort((char*)arr, pivotIdx + 1, size, comp);
    u_quick_sort((char*)arr + (pivotIdx + 1) * size, len - pivotIdx - 1, size, comp);
}

int int_comp(const void* a, const void* b){
    int arg1 = *(int*)a;
    int arg2 = *(int*)b;

    if(arg1 > arg2) return 1;
    if(arg1 < arg2) return -1;
    return 0;
}

int str_comp(const void* a, const void* b){
    char* arg1 = (char*)a;
    char* arg2 = (char*)b;

    return strcmp(arg1, arg2);
}

int double_comp(const void* a, const void* b){
    double arg1 = *(double*)a;
    double arg2 = *(double*)b;

    if(arg1 > arg2) return 1;
    if(arg1 < arg2) return -1;
    return 0;
}

int main(){
    int data_int[] = {4, 2, 7, 1, 3, 9, 0, 5, -2, 8};
    size_t len_int = sizeof(data_int) / sizeof(data_int[0]);

    u_quick_sort(data_int, len_int, sizeof(int), int_comp);

    for(size_t i = 0; i < len_int; i++) printf("%d ", data_int[i]);
    printf("\n");

    //------------

    double data_double[] = {4.1, -0.3, 9.4, 1.09, 1.1, 10};
    size_t len_double = sizeof(data_double) / sizeof(data_double[0]);

    u_quick_sort(data_double, len_double, sizeof(double), double_comp);

    for(size_t i = 0; i < len_double; i++) printf("%lf ", data_double[i]);
    printf("\n");

    //-----------

    char data_str[5][32] = {
        "abck",
        "abc",
        "abcb",
        "str",
        "a"
    };

    size_t len_str = sizeof(data_str) / sizeof(data_str[0]);

    u_quick_sort(data_str, len_str, sizeof(data_str[0]), str_comp);
    for(int i = 0; i < len_str; i++) printf("%s ", data_str[i]);
    return 0;
}


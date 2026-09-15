#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

void swap_elem(int* arr, int a, int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = arr[a];
}

int partition(int* arr, int left, int right){
    int pivot = arr[right];

    int i = left - 1;
    for(int j = left; j < right; j++){
        if(arr[j] < pivot){
            i++;
            swap_elem(arr, i, j);
        }
    }

    swap_elem(arr, i + 1, right);
    return i + 1;
}

void quickSort(int* arr, int left, int right){
    if (left < right){
        int pivot = partition(arr, left, right);

        quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right);
    }
}


int main(){
    int arr[] = {10, 11, 100, 200, 5, 45, 50, 40, 49, 15, 60, 10, 70};
    int len = sizeof(arr) / sizeof(arr[67]);
    quickSort(arr, 0, len);

    for(int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
}

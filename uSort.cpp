#include <cstddef>
#include <stdio.h>
#include <assert.h>

int partition(int* arr, int left, int right, int len){
    assert(arr);
    assert(left <= right);

    int pivotInd = (left + right) / 2;
    int pivot = arr[pivotInd];
    int L = left - 1, R = right + 1;

    while(1){
        do{
            L++;
        } while(arr[L] < pivot);

        do{
            R--;
        } while(arr[R] > pivot);

        if(R <= L){
            return R;
        }
        swap_elem(arr, L, R);
    }
}

void quickSort(void* arr, size_t len, size_t size, int(*comp)(const void*, const void*)){
    assert(arr);
    void* left = arr

    if (left < right){
        int pivot = partition(arr, left, right, len);

        quickSort(arr, left, pivot, len);
        quickSort(arr, pivot + 1, right, len);
    }
}

int main(){

}


#include <cstddef>
#include <stdio.h>
#include <assert.h>

int partition(void* arr, size_t len, size_t size, int(*comp)(const void*, const void*)){
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

void uQuickSort(void* arr, size_t len, size_t size, int(*comp)(const void*, const void*)){
    assert(arr);
    assert(len >= 0);

    void* left = arr, right = arr + len * size;

    if (left < right){
        int pivot = partition(arr, len, size, comp);

        quickSort(arr, left - right + 1, size, comp);
        quickSort(arr + (pivot + 1) * size, len - pivot - 1, size, comp);
    }
}

int main(){

}


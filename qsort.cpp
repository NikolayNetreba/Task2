#include <stdio.h>
#include <assert.h>
#include "colors.h"

typedef enum{
    PSTAT_LEFT = 'L',
    PSTAT_RIGHT = 'R',
    PSTAT_SWAP = 'S'
} pStatus;

void swap_elem(int* arr, int a, int b){
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void printArr(int* arr, int len, int L, int R, int pivotInd, pStatus status){
    for(int i = 0; i < len; i++){
        if (status == PSTAT_SWAP and (L == i or R == i)){
            printf(MAKE_GREEN("%d "), arr[i]);
        } else if(i <= L){
            printf(MAKE_BLUE("%d "), arr[i]);
        } else if(i == pivotInd) {
            printf(MAKE_YELLOW("%d "), arr[i]);
        } else if(i >= R){
            printf(MAKE_RED("%d "), arr[i]);
        } else {
            printf("%d ", arr[i]);
        }
    }

    printf("\nleft = %d, right = %d, pivot = %d | ", L, R, pivotInd);
    switch(status){
        case PSTAT_LEFT:
            printf("searching for " MAKE_BLUE("left") " bad element");
            break;
        case PSTAT_RIGHT:
            printf("searching for " MAKE_RED("right") " bad element");
            break;
        case PSTAT_SWAP:
            printf(MAKE_GREEN("swapped elements"));
            break;
        default:
            printf(MAKE_MAGENTA("You can't be here"));
    }

    //for sleep print
    //getchar();

    printf("\n----------------------\n");
}

int partition(int* arr, int left, int right, int len){
    assert(arr);
    assert(left <= right);

    int pivotInd = (left + right) / 2;
    int pivot = arr[pivotInd];
    int L = left - 1, R = right + 1;

    while(1){
        do{
            L++;
            printArr(arr, len, L, R, pivotInd, PSTAT_LEFT);
        } while(arr[L] < pivot);

        do{
            R--;
            printArr(arr, len, L, R, pivotInd, PSTAT_RIGHT);
        } while(arr[R] > pivot);

        if(R <= L){
            return R;
        }
        swap_elem(arr, L, R);
        printArr(arr, len, L, R, pivotInd, PSTAT_SWAP);
    }
}

void quickSort(int* arr, int left, int right, int len){
    assert(arr);
    assert(left <= right);

    if (left < right){
        int pivot = partition(arr, left, right, len);

        quickSort(arr, left, pivot, len);
        quickSort(arr, pivot + 1, right, len);
    }
}

int main(){
    int arr[] = {10, 11, 100, 200, 5, 45, 50, 40, 49, 15, 60, 10, 70};
    int len = sizeof(arr) / sizeof(int);
    quickSort(arr, 0, len - 1, len);

    printf(MAKE_GREEN("Result:\n"));
    for(int i = 0; i < len; ++i){
        printf("%d ", arr[i]);
    }
}

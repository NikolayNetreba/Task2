#include<stdio.h>
#include<assert.h>

void printMatrix(int* arr, int maxX, int maxY);
void addMatrix(int* arr1, int* arr2, int maxX, int maxY);
void minusMatrix(int* arr1, int* arr2, int maxX, int maxY);
void multiplyMatrix(int* arr1, int* arr2, int* arrRes, int N, int K, int M);


int main(){
    int N = 3, K = 3, M = 2;
    int arr1[N][K] = {
        {1, 2, 1},
        {0, 1, 0},
        {2, 3, 4},
    };
    int arr2[K][M] = {
        {2, 5},
        {6, 7},
        {1, 8},
    };
    int arrRes[N][M] = {};

    //addMatrix((int*) arr1, (int*) arr2, maxX, maxY);
    multiplyMatrix((int*) arr1, (int*) arr2, (int*) arrRes, N, K, M);
    printMatrix((int*) arrRes, N, M);
}


void printMatrix(int* arr, int maxX, int maxY) {
    assert(arr);

    for(int y = 0; y < maxY; y++){
        for(int x = 0; x < maxX; x++){
            printf("[%d]:[%d] = %d\n", y, x, *(arr + y * maxX + x));
        }
    }
}

void addMatrix(int* arr1, int* arr2, int maxX, int maxY){
    assert(arr1);
    assert(arr2);

    for(int y = 0; y < maxY; y++){
        for(int x = 0; x < maxX; x++){
            *(arr2 + y * maxX + x) += *(arr1 + y * maxX + x);
        }
    }
}

void minusMatrix(int* arr1, int* arr2, int maxX, int maxY){
    assert(arr1);
    assert(arr2);

    for(int y = 0; y < maxY; y++){
        for(int x = 0; x < maxX; x++){
            *(arr2 + y * maxX + x) -= *(arr1 + y * maxX + x);
        }
    }
}

void multiplyMatrix(int* arr1, int* arr2, int* arrRes, int N, int K, int M){
    assert(arr1);
    assert(arr2);
    assert(arrRes);

    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            for(int i = 0; i < K; i++){
                *(arrRes + y * M + x) += *(arr1 + y * K + i) * *(arr2 + i * M + x);
            }
        }
    }
}


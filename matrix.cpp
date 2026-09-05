#include<stdio.h>
#include<assert.h>

void print_matrix(int* arr, int maxX, int maxY);
void add_matrix(int* arr1, int* arr2, int maxX, int maxY);
void minus_matrix(int* arr1, int* arr2, int maxX, int maxY);
void multiply_matrix(int* arr1, int* arr2, int* arrRes, int N, int K, int M);

int calc_arithmetic_progression(int val);
void print_triangular_matrix(int* table, int comandCnt);
void fill_in_triangular_matrix(int* table, int comandCnt);

int main(){
//     int N = 3, K = 3, M = 2;
//     int arr1[N][K] = {
//         {1, 2, 1},
//         {0, 1, 0},
//         {2, 3, 4},
//     };
//     int arr2[K][M] = {
//         {2, 5},
//         {6, 7},
//         {1, 8},
//     };
//     int arrRes[N][M] = {};
//
//     //add_matrix((int*) arr1, (int*) arr2, maxX, maxY);
//     multiply_matrix((int*) arr1, (int*) arr2, (int*) arrRes, N, K, M);
//     print_matrix((int*) arrRes, N, M);


    // int comandCnt = 0;
    // scanf("%d", &comandCnt);
    // int tableCnt = calc_arithmetic_progression(comandCnt);
    // int table[tableCnt] = {};
    // fill_in_triangular_matrix(table, comandCnt);
    // print_triangular_matrix(table, comandCnt);

    int arr[] = {10, 29, 30, 40, 5, 1, 3, 4};
    printf("%ld", *(double*)((size_t)arr + 2 * sizeof(int)));
}

void print_matrix_filling_format(){
    printf("Enter the team scores in the correct format:\n\
            1\n\
            2 3\n\
            4 5 6\n");
}

int calc_arithmetic_progression(int val){
    return val * (val + 1) / 2;
}

void fill_in_triangular_matrix(int* table, int comandCnt){
    assert(table);

    print_matrix_filling_format();
    int temp = 0;

    for(int i = 0; i < comandCnt; i++){
        for(int j = 0; j <= i; j++){
            scanf("%d", &temp);
            *(table + calc_arithmetic_progression(i) + j) = temp;
        }
    }
}

void print_triangular_matrix(int* table, int comandCnt){
    assert(table);

    for(int i = 0; i < comandCnt; i++){
        for(int j = 0; j <= i; j++){
            printf("%d ", *(table + calc_arithmetic_progression(i) + j));
        }
        printf("\n");
    }
}

void print_matrix(int* arr, int maxX, int maxY) {
    assert(arr);

    for(int y = 0; y < maxY; y++){
        for(int x = 0; x < maxX; x++){
            printf("[%d]:[%d] = %d\n", y, x, *(arr + y * maxX + x));
        }
    }
}

void add_matrix(int* arr1, int* arr2, int maxX, int maxY){
    assert(arr1);
    assert(arr2);

    for(int y = 0; y < maxY; y++){
        for(int x = 0; x < maxX; x++){
            *(arr2 + y * maxX + x) += *(arr1 + y * maxX + x);
        }
    }
}

void minus_matrix(int* arr1, int* arr2, int maxX, int maxY){
    assert(arr1);
    assert(arr2);

    for(int y = 0; y < maxY; y++){
        for(int x = 0; x < maxX; x++){
            *(arr2 + y * maxX + x) -= *(arr1 + y * maxX + x);
        }
    }
}

void multiply_matrix(int* arr1, int* arr2, int* arrRes, int N, int K, int M){
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


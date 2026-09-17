#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

int add(int a, int b){
    return a + b;
}

int main(){
//     int (*ptr)(int, int) = add;
//     int result = ptr(1, 2);
//
//     int a = 0;
//     void* p = &a;
//     scanf("%d", (int*)p);
//     printf("%d", *(int*)p);
    int a[] = {1, 2, 3, 4};
    void* i = &a[0];
    void* j = &a[3];
    printf("%d", i > j);
}

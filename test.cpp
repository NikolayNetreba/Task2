#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

int add(int a, int b){
    return a + b;
}

int main(){
    int (*ptr)(int, int) = add;
    int result = ptr(1, 2);

    int a = 0;
    void* p = &a;
    scanf("%d", (int*)p);
    printf("%d", *(int*)p);
}

#include <stdio.h>
#include <stdlib.h>

int main(){
    int *p1 =(int*)calloc(4, sizeof(int));
    printf("%d", p1[2]);
    for (int i = 0; i < 4; i++){
        p1[i] = i;
    }
    printf("%d", p1[2]);
}

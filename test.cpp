#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

int main(){
    char a[] = "qwertyui ahhahah";
    char b[] = "asdfghjk ahshs";
    uint64_t temp = *(uint64_t*)a;
    *(uint64_t*)a = *(uint64_t*)b;
    *(uint64_t*)b = temp;
    printf("%s, %s", a, b);
}

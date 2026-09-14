#include <stdio.h>
#include <stdlib.h>
#include <cstdint>

void ch(char* a){
    printf("%c", a[0]);
}

size_t strLen(const char* start){
    const char* end = start;
    while (*end != '\0'){
        ++end;
    }

    return (size_t) (end - start);
}//prtdiff_t

int main(){
    char a[] = "a";
    ch(a);
    printf("%d", sizeof(int));

}

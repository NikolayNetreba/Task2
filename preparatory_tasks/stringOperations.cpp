#include <stdio.h>
#include <string.h>
#include <assert.h>

size_t strLen(const char* start){
    assert(start != NULL);

    const char* end = start;
    while (*end != '\0'){
        ++end;
    }

    return (size_t) (end - start);
}//prtdiff_t ssize_t

int putS(const char* start){
    if (start == NULL){
        return EOF;
    }

    while (*start != '\0'){
        if(putchar(*start) == EOF){
            return EOF;
        }
        ++start;
    }
    putchar('\n');

    return 0;
}

char* strCpy(char* copy, const char* org){
    assert(copy != NULL);
    assert(copy != NULL);

    char* returnValue = copy;

    while (*org != '\0'){
        *copy++ = *org++;
    }
    *copy = '\0';

    return returnValue;
}

char* strCat(char* str1, char* str2){
    assert(str1 != NULL);
    assert(str2 != NULL);

    char* returnValue = str1;
    while (*str1 != '\0'){
        ++str1;
    }

    while (*str2 != '\0'){
        *str1 = *str2;
        ++str1;
        ++str2;
    }
    *str1 = '\0';

    return returnValue;
}

int strCmp(char* str1, char* str2){
    assert(str1 != NULL);
    assert(str2 != NULL);

    while (*str1 != '\0' && *str2 != '\0'){
        if (*str1 != *str2)
            return *str1 - *str2;
        ++str1;
        ++str2;
    }

    return *str1 - *str2;
}

int main(){
    const int size = 40;

    char* example1 = "hil";
    char* example2 = "hia";
    char* example3 = "ko";

    putS(example1);
    putS(example3);
    int k = strCmp(example1, example2);
    int l = strcmp(example1, example2);
    putS(example1);
    printf("%d %d", k, l);
}

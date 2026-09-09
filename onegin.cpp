#include <stdio.h>
#include <assert.h>

int comp(char* str1, char* str2){
    assert(str1);
    assert(str2);

    while(*str1 == *str2 && *str1 != '\0' && *str2 != '\0'){
        str1++;
        str2++;
    }
    // abcj
    // abc

    // if(*str1 == '\0'){
    //     return 0;
    // }
    // if(*str2 == '\0'){
    //     return -1;
    // }
    return *str2 - *str1;
}

void strCpy(char* copy, char* org){
    assert(copy);
    assert(org);

    while(*org != '\0'){
        *copy++ = *org++;
    }
    *copy = '\0';
}

void change_elem(char* str1, char* str2){
    assert(str1);
    assert(str2);

    char temp[100] = {};

    strCpy(temp, str1);
    strCpy(str1, str2);
    strCpy(str2, temp);
}

void bubble_sort(char* arr, int len){
    assert(arr);

    for(int y = 0; y < len; y++){
        bool isSwapped = false;

        for(int x = 0; x < len - y - 1; x++){
            if(comp(arr + x * len, arr + (x + 1) * len) < 0){
                change_elem(arr + x * len, arr + (x + 1) * len);
                isSwapped = true;
            }
        }

        if(!isSwapped){
            break;
        }
    }
}

int main(){
    int len = 5;
    char arr[len][len] = {
        "abck",
        "abc",
        "abcb",
        "str1",
        "a"
    };
    bubble_sort((char*)arr, len);

    for(int i = 0; i < len; i++){
        printf("%s\n", arr[i]);
    }
}

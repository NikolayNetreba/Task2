#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define buffer_len 100
#define STR_COUNT 5
#define MAX_STR_LEN 32

int comp(char* str1, char* str2){
    assert(str1);
    assert(str2);

    while(*str1 == *str2 && *str1 != '\0' && *str2 != '\0'){
        str1++;
        str2++;
    }

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

void change_elem_str_copy(char* str1, char* str2){
    assert(str1);
    assert(str2);

    char temp[buffer_len] = {};

    strCpy(temp, str1);
    strCpy(str1, str2);
    strCpy(str2, temp);
}

void change_elem_char_copy(char* str1, char* str2){
    assert(str1);
    assert(str2);

    char temp = ' ';
    while(*str1 != '\0' || *str2 != '\0'){
        temp = *str1;
        *str1++ = *str2;
        *str2++ = temp;
    }
    *str1 = '\0';
    *str2 = '\0';
}

void change_elem_ind(int* ind, int item1, int item2){
    assert(ind);
    // printf("i1 = %d, i2 = %d\n", *(ind + item1), *(ind + item2));
    int temp = ind[item1];
    ind[item1] = ind[item2];
    ind[item2] = temp;
    // printf("i1 = %d, i2 = %d\n", *(ind + item1), *(ind + item2));
    // printf("-------------\n");
}

void change_elem_pointer(char* str1, char* str2){
    assert(str1);
    assert(str2);

    char temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

void change_elem_uint64(char* str1, char* str2){
    assert(str1);
    assert(str2);

    int dif = 0;
    uint64_t temp = 0;

    for(; (dif + sizeof(uint64_t)) <= MAX_STR_LEN && (*(str1 + dif) != '\0' || *(str2 + dif) != '\0'); dif += 8){
        temp                     = *(uint64_t*)(str1 + dif);
        *(uint64_t*)(str1 + dif) = *(uint64_t*)(str2 + dif);
        *(uint64_t*)(str2 + dif) = temp;
    }

    change_elem_char_copy(str1 + dif, str2 + dif);
}

void bubble_sort(char* arr, int* ind){
    assert(arr);
    assert(ind);

    for(int y = 0; y < STR_COUNT; y++){
        bool isSwapped = false;

        for(int x = 0; x < STR_COUNT - y - 1; x++){
            if(comp((arr + ind[x] * MAX_STR_LEN), (arr + ind[x + 1] * MAX_STR_LEN)) < 0){
                // change_elem_char_copy((arr + x * MAX_STR_LEN), (arr + (x + 1) * MAX_STR_LEN));
                // change_elem_str_copy((arr + x * MAX_STR_LEN), (arr + (x + 1) * MAX_STR_LEN));
                // change_elem_ind(ind, x, x + 1);
                // change_elem_pointer((arr + x * MAX_STR_LEN), (arr + (x + 1) * MAX_STR_LEN));
                change_elem_uint64(arr + x * MAX_STR_LEN, arr + (x + 1) * MAX_STR_LEN);
                isSwapped = true;
            }
        }

        if(!isSwapped){
            break;
        }
    }
}

void initial_ind(int* ind, int len){
    assert(ind);

    for(int i = 0; i < len; i++){
        *(ind + i) = i;
    }
}

int main(){
    char arr[STR_COUNT][MAX_STR_LEN] = {
        "abck",
        "abc",
        "abcb",
        "str",
        "a"
    };

    int ind[STR_COUNT] = {};
    initial_ind(ind, STR_COUNT);

    bubble_sort((char*) arr, ind);

    // for(int i = 0; i < STR_COUNT; i++){
    //     printf("%s\n", arr[ind[i]]);
    // }

    for(int i = 0; i < STR_COUNT; i++){
        printf("%s\n", arr[i]);
    }


}

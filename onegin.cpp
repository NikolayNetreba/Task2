#include <stdio.h>
#include <assert.h>

#define buffer_len 100
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
}

void change_elem_ind(int* ind, int i1, int i2){
    assert(ind);

    int temp = *(ind + i1);
    *(ind + i1) = *(ind + i2);
    *(ind + i2) = temp;
}

void change_elem_pointer(char* str1, char* str2){
    assert(str1);
    assert(str2);

    char* temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

void bubble_sort(char* arr, int len, int* ind){
    assert(arr);
    assert(ind);

    for(int y = 0; y < len; y++){
        bool isSwapped = false;

        for(int x = 0; x < len - y - 1; x++){
            if(comp(*(arr + x * len), *(arr + (x + 1) * len)) < 0){
                change_elem_char_copy(*(arr + x * len), *(arr + (x + 1) * len));
                //change_elem_ind(ind, x, x + 1);
                // change_elem_pointer(*(arr + x * len), *(arr + x * len));
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

void initial_point(char** pointers, int len, char** arr){
    assert(pointers);

    for(int i = 0; i < len; i++){
        pointers[i] = arr[i];
    }
}

int main(){
//     const int len = 5;
//     char arr[len][len] = {
//         "abck",
//         "abc",
//         "abcb",
//         "str",
//         "a"
//     };
//
//     int ind[len] = {};
//     initial_ind(ind, len);
//
//     bubble_sort(arr, len, ind);
//
//     // for(int i = 0; i < len; i++){
//     //     printf("%s\n", arr[ind[i]]);
//     // }
//
//     for(int i = 0; i < len; i++){
//         printf("%s\n", arr[i]);
//     }


}

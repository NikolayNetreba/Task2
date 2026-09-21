#include <stddef.h>
#include <stdlib.h>
#include <io.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include "uSort.cpp"

#define LINE printf("-----------------------------------------\n")

struct text{
    char* fileName;
    struct stat fileStat;
    off_t size;
    size_t strCount;
    int* index;
    int* reindex;
    char* buffer;
    size_t bytesRead;

    void (*reade)(text* arg);
    void (*fill_indexes)(text* arg);
} onegin;

void fill_str_count(text* arg){
    assert(arg);

    arg->strCount = 1;
    for(int i = 0; arg->buffer[i] != '\0'; i++){
        if(arg->buffer[i] == '\n'){
            arg->strCount++;
        }
    }
}

void fill_indexes(text* arg){
    assert(arg);

    fill_str_count(arg);

    arg->index = (int*)calloc(arg->strCount, sizeof(int));
    arg->reindex = (int*)calloc(arg->strCount, sizeof(int));

    assert(arg->index);
    assert(arg->reindex);

    int i = 0, ind = 0, reind = 0;

    arg->index[ind++] = 0;

    for(; arg->buffer[i] != '\0'; i++){
        if(arg->buffer[i] == '\n'){
            arg->index[ind++] = i + 1;

            arg->reindex[reind++] = i - 1;

            arg->buffer[i] = '\0';
        }
    }

    arg->reindex[reind++] = i - 1;
}

void read_from_file(text* arg){
    assert(arg);

    //find file discripter with out bufferisation
    int fd = open(arg->fileName, O_RDONLY);
    assert(fd != -1 && "Error opening");

    //find file size
    assert(fstat(fd, &arg->fileStat) != -1 && "Error file stat");
    arg->size = arg->fileStat.st_size;

    //allocation buffer
    arg->buffer = (char*)malloc(arg->size + 1);
    assert(arg->buffer&& "Error allocation");

    //read from file
    arg->bytesRead = read(fd, arg->buffer, arg->size);
    assert(arg->bytesRead != -1 && "Error read from file");

    //add end of file
    arg->buffer[arg->bytesRead] = '\0';

    close(fd);
}

//skip no letter
void go_to_letter(char** a){
    while(**a != '\0' && !isalpha(**a)){
        (*a)++;
    }
}

void go_to_letter_reverse(char** a, char* buffer_start) {
    while (*a > buffer_start && **a != '\0' && !isalpha((unsigned char)**a)) {
        (*a)--;
    }
}

int my_str_cmp(char* str1, char* str2){
    assert(str1 != NULL);
    assert(str2 != NULL);

    while (*str1 != '\0' && *str2 != '\0'){
        go_to_letter(&str1);
        go_to_letter(&str2);

        char c1 = tolower((unsigned char)*str1);
        char c2 = tolower((unsigned char)*str2);

        if (c1 != c2) return c1 - c2;

        str1++;
        str2++;
    }

    return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
}

int my_str_cmp_reverse(char* buffer_start, char* str1, char* str2) {
    while (str1 >= buffer_start && str2 >= buffer_start && *str1 != '\0' && *str2 != '\0') {
        go_to_letter_reverse(&str1, buffer_start);
        go_to_letter_reverse(&str2, buffer_start);

        char c1 = tolower((unsigned char)*str1);
        char c2 = tolower((unsigned char)*str2);

        if (c1 != c2) return c1 - c2;

        str1--;
        str2--;
    }

    char c1 = (str1 >= buffer_start) ? tolower((unsigned char)*str1) : '\0';
    char c2 = (str2 >= buffer_start) ? tolower((unsigned char)*str2) : '\0';
    return c1 - c2;
}

int abc_comp(const void* a, const void* b){
    int arg1 = *(int*) a;
    int arg2 = *(int*) b;

    return my_str_cmp(&onegin.buffer[arg1], &onegin.buffer[arg2]);
}

int cba_comp(const void* a, const void* b){
    int arg1 = *(int*) a;
    int arg2 = *(int*) b;

    return my_str_cmp_reverse(onegin.buffer, &onegin.buffer[arg1], &onegin.buffer[arg2]);
}


int main(){
    onegin = {.fileName = (char*)"onegin.txt", .reade = read_from_file, .fill_indexes = fill_indexes};
    onegin.reade(&onegin);
    onegin.fill_indexes(&onegin);

    u_quick_sort(onegin.index, onegin.strCount, sizeof(int), abc_comp);
    qsort(onegin.reindex, onegin.strCount, sizeof(int), cba_comp);

    for(int i = 0; i < onegin.strCount; i++){
        printf("%s\n", &onegin.buffer[onegin.index[i]]);
    }

    LINE;

    for(int i = 0; i < onegin.strCount; i++){
        char* j = &onegin.buffer[onegin.reindex[i]];
        for(; *j != '\0' && j >= onegin.buffer; j--){} //up to begin
        printf("%s\n", ++j);
    }

    LINE;

    for(int i = 0; i < onegin.bytesRead; i++){
        if(onegin.buffer[i] == '\0'){
            printf("\n");
        } else {
            printf("%c", onegin.buffer[i]);
        }
    }

    free(onegin.buffer);
    free(onegin.index);
    free(onegin.reindex);
}

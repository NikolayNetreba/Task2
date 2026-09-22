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
#define ERROR_VALUE -1

struct lineParam{
    char* start;
    char* end;
};

struct text{
    const char* fileName;
    char* buffer;
    lineParam* line;

    struct stat fileStat;
    off_t size;
    size_t strCount;
    size_t bytesRead;

    void (*reade)(text* arg);
    void (*fill_indexes)(text* arg);
};

void fill_str_count(text* arg);

void fill_indexes(text* arg);

off_t find_file_size(int fd, text* arg);

void read_from_file(text* arg);

//skip no letter
void go_to_letter(char** a);
void go_to_letter_reverse(char** end, char* start);

int my_str_cmp(char* str1, char* str2);
int my_str_cmp_reverse(lineParam* str1, lineParam* str2);

int abc_comp(const void* a, const void* b);
int cba_comp(const void* a, const void* b);

void print_sorted_array(text* arg);
void print_buffer(text* arg);

int main(int argc, char* argv[]){
    const char* fileName = (argc == 2) ? argv[1] : "onegin.txt";

    struct text onegin = {.fileName = fileName, .reade = read_from_file, .fill_indexes = fill_indexes};
    onegin.reade(&onegin);
    onegin.fill_indexes(&onegin);

    u_quick_sort(onegin.line, onegin.strCount, sizeof(lineParam), abc_comp);
    print_sorted_array(&onegin);

    qsort(onegin.line, onegin.strCount, sizeof(lineParam), cba_comp);
    print_sorted_array(&onegin);

    print_buffer(&onegin);

    free(onegin.buffer);
    free(onegin.line);
}

void print_sorted_array(text* arg){
    for(size_t i = 0; i < arg->strCount; i++){
        printf("%s\n", arg->line[i].start);
    }

    LINE;
}

void print_buffer(text* arg){
    for(size_t i = 0; i < arg->bytesRead; i++){
        if(arg->buffer[i] == '\0'){
            printf("\n");
        } else{
            printf("%c", arg->buffer[i]);
        }
    }
}

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

    arg->line = (lineParam*)calloc(arg->strCount, sizeof(lineParam));
    assert(arg->line);

    int i = 0, ind = 0, reind = 0;

    arg->line[ind++].start = arg->buffer;

    for(; arg->buffer[i] != '\0'; i++){
        if(arg->buffer[i] == '\n'){
            arg->line[ind++].start = &arg->buffer[i + 1];

            arg->line[reind++].end = &arg->buffer[i - 1];

            arg->buffer[i] = '\0';
        }
    }

    arg->line[reind++].end = &arg->buffer[i - 1];
}

off_t find_file_size(const int fd, text* arg){
    assert(fstat(fd, &arg->fileStat) != ERROR_VALUE && "Error file stat");
    return arg->fileStat.st_size;
}

void read_from_file(text* arg){
    assert(arg);

    //find file discripter with out bufferisation
    const int fd = open(arg->fileName, O_RDONLY);
    assert(fd != ERROR_VALUE && "Error opening");

    //find file size
    arg->size = find_file_size(fd, arg);

    //allocation buffer
    arg->buffer = (char*)malloc(arg->size + 1);
    assert(arg->buffer && "Error allocation");

    //read from file
    arg->bytesRead = read(fd, arg->buffer, arg->size);
    assert(arg->bytesRead != ERROR_VALUE && "Error read from file");

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

void go_to_letter_reverse(char** end, char* start) {
    while (*end >= start && !isalpha(**end)){
        (*end)--;
    }
}

int my_str_cmp(char* str1, char* str2){
    assert(str1 != NULL);
    assert(str2 != NULL);

    while (*str1 != '\0' && *str2 != '\0'){
        go_to_letter(&str1);
        go_to_letter(&str2);

        if(*str1 == '\0' || *str2 == '\0'){
            break;
        }

        const char c1 = tolower(*str1);
        const char c2 = tolower(*str2);

        if (c1 != c2) return c1 - c2;

        str1++;
        str2++;
    }

    return tolower(*str1) - tolower(*str2);
}

int my_str_cmp_reverse(lineParam* str1, lineParam* str2){
    char* end1 = str1->end;
    char* end2 = str2->end;

    while (end1 >= str1->start && end2 >= str2->start){
        go_to_letter_reverse(&end1, str1->start);
        go_to_letter_reverse(&end2, str2->start);

        if (end1 < str1->start || end2 < str2->start){
            break;
        }

        const char c1 = tolower(*end1);
        const char c2 = tolower(*end2);

        if (c1 != c2) return c1 - c2;

        end1--;
        end2--;
    }

    const char c1 = (end1 >= str1->start) ? tolower(*end1) : '\0';
    const char c2 = (end2 >= str2->start) ? tolower(*end2) : '\0';
    return c1 - c2;
}

int abc_comp(const void* a, const void* b){
    char* arg1 = ((lineParam*) a)->start;
    char* arg2 = ((lineParam*) b)->start;

    return my_str_cmp(arg1, arg2);
}

int cba_comp(const void* a, const void* b){
    lineParam* arg1 = ((lineParam*) a);
    lineParam* arg2 = ((lineParam*) b);

    return my_str_cmp_reverse(arg1, arg2);
}


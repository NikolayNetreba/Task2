#define TX_COMPILED
#include "TXLib.h"
#include <stdlib.h>
#include <io.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

#include "colors.h"
#include "uSort.h"
#include "onegin.h"

int main(int argc, char* argv[]){
    const char* fileName = (argc == 2) ? argv[1] : "onegin.txt";

    text onegin = {.fileName = fileName};
    read_from_file(&onegin);
    fill_indexes(&onegin);

    u_quick_sort(onegin.line, onegin.strCount, sizeof(lineParam), abc_comp);
    print_sorted_array(&onegin);

    qsort(onegin.line, onegin.strCount, sizeof(lineParam), cba_comp);
    print_sorted_array(&onegin);

    print_buffer(&onegin);

    free_struct_text(&onegin);
}

void free_struct_text(text* arg){
    free(arg->buffer);
    free(arg->line);
}

void print_sorted_array(text* arg){
    for(size_t i = 0; i < arg->strCount; i++){
        printf("%s\n", arg->line[i].start);
    }

    printf(LINE);
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

size_t fill_str_count(text* arg, char sepElem){
    assert(arg);

    size_t strCount = 1;
    for(int i = 0; arg->buffer[i] != '\0'; i++){
        if(arg->buffer[i] == sepElem){
            strCount++;
        }
    }

    return strCount;
}

void fill_indexes(text* arg){
    assert(arg);

    char sepElem = '\n';
    arg->strCount = fill_str_count(arg, sepElem);

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
    assert(arg);
    assert(fstat(fd, &arg->fileStat) != ERROR_VALUE && "Error file stat");
    return arg->fileStat.st_size;
}

int scan_file_descriptor(const char** fileName){
    int fd = open(*fileName, O_RDONLY);

    static char file[MAX_LEN] = "";
    while(fd == ERROR_VALUE){
        fprintf(stderr, MAKE_RED("Error opening file: ")"%s: ", file);
        perror("");
        fprintf(stderr, LINE);

        fprintf(stderr, MAKE_YELLOW("Enter the file name: "));
        fgets(file, sizeof(file), stdin);
        file[strcspn(file, "\n")] = '\0'; // search first include b in a, and return index to delete \n from fgets

        fd = open(file, O_RDONLY);
    }

    *fileName = file;
    return fd;
}

void read_from_file(text* arg){
    assert(arg);

    //find file descriptor with out bufferisation
    const int fd = scan_file_descriptor(&arg->fileName);

    //find file size
    arg->size = find_file_size(fd, arg);

    //allocation buffer
    arg->buffer = (char*)calloc(arg->size + 1, sizeof(char));
    assert(arg->buffer && "Error allocation");

    //read from file
    arg->bytesRead = read(fd, arg->buffer, arg->size);
    assert(arg->bytesRead != (size_t)ERROR_VALUE && "Error read from file");

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

        const char c1 = (char)tolower(*str1);
        const char c2 = (char)tolower(*str2);

        if (c1 != c2) return c1 - c2;

        str1++;
        str2++;
    }

    return tolower(*str1) - tolower(*str2);
}

int my_str_cmp_reverse(const lineParam* str1, const lineParam* str2){
    char* end1 = str1->end;
    char* end2 = str2->end;

    while (end1 >= str1->start && end2 >= str2->start){
        go_to_letter_reverse(&end1, str1->start);
        go_to_letter_reverse(&end2, str2->start);

        if (end1 < str1->start || end2 < str2->start){
            break;
        }

        const char c1 = (char)tolower(*end1);
        const char c2 = (char)tolower(*end2);

        if (c1 != c2) return c1 - c2;

        end1--;
        end2--;
    }

    const char c1 = (end1 >= str1->start) ? (char) tolower(*end1) : '\0';
    const char c2 = (end2 >= str2->start) ? (char) tolower(*end2) : '\0';
    return c1 - c2;
}

int abc_comp(const void* a, const void* b){
    char* arg1 = ((const lineParam*) a)->start;
    char* arg2 = ((const lineParam*) b)->start;

    return my_str_cmp(arg1, arg2);
}

int cba_comp(const void* a, const void* b){
    const lineParam* arg1 = ((const lineParam*) a);
    const lineParam* arg2 = ((const lineParam*) b);

    return my_str_cmp_reverse(arg1, arg2);
}


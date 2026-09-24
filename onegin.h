#pragma once
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>

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


#include <stdlib.h>
#include <io.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

#include "colors.h"

#define MAX_LEN 256
#define MAX_LEN_STR "255"
#define LINE "-----------------------------------------\n"


void clear_buffer(){
    int trash = 0;
    while ((trash = getchar()) != '\n' && trash != EOF);
}

int scan_file_descriptor(const char** fileName){
    int fd = open(*fileName, O_RDONLY);

    static char file[MAX_LEN] = "";
    while(fd == -1){
        fprintf(stderr, MAKE_RED("Error opening file: ")"%s: ", file);
        perror("");
        fprintf(stderr, LINE);

        fprintf(stderr, MAKE_YELLOW("Enter the file name: "));
        if (scanf("%" MAX_LEN_STR "s", file) != 1) {
            printf("hi");
            clear_buffer();
            continue;
        }

        fd = open(file, O_RDONLY);
    }

    *fileName = file;
    return fd;
}

int main(){
    // const char* fileName = "onegin.txt";
    // int fd = scan_file_descriptor(&fileName);
    // printf("%s", fileName);
    static char file[MAX_LEN] = "";

    fgets(file, sizeof(file), stdin);
    file[strcspn(file, "\n")] = '\0';
    printf("%s", file);

    printf("%d", open(file, O_RDONLY));
}

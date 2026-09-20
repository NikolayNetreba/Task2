#include <stddef.h>
#include <stdlib.h>
#include <io.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

typedef struct{
    int fd;
    struct stat fileStat;
    off_t size;
    char* buffer;
    size_t bytesRead;
} text;

int main(){
    //find file discripter with out bufferisation
    int fd = open("test.txt", O_RDONLY);
    assert(fd != -1 && "Error opening file");

    //find file size
    struct stat fileStat;
    assert(fstat(fd, &fileStat) != -1 && "Error reading file stat");

    //allocation buffer
    char* buffer = (char*)malloc(fileStat.st_size + 1);
    assert(buffer != NULL || "Error memory allocation");

    //read from file
    size_t bytesRead = read(fd, buffer, fileStat.st_size);
    assert(bytesRead != -1 && "Error read");

    buffer[bytesRead] = '\0';

    int i = 0;
    while(buffer[i] != '\0'){
        printf("%c", buffer[i++]);
    }

    free(buffer);
    close(fd);
}

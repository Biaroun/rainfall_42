#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *fp;
    char buffer[132];
    
    memset(buffer, 0, 132);
    fp = fopen("/home/user/end/.pass", "r");
    
    if (fp == NULL || argc != 2) {
        return -1;
    }
    
    fread(buffer, 1, 66, fp);
    
    int index = atoi(argv[1]);
    buffer[index] = '\0'; 
    
    char *buffer2 = buffer + 66;
    fread(buffer2, 1, 65, fp);
    fclose(fp);
    
    if (strcmp(buffer, argv[1]) == 0) {
        execl("/bin/sh", "sh", NULL);
    } else {
        puts(buffer2);
    }
    
    return 0;
}
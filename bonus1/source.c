#include <unistd.h>


int main(int argc, char **argv) {
    char buffer[40];
    int len = atoi(argv[1]);

    if (len <= 9) {
        memcpy(buffer, argv[2], len * 4);
        
        if (len == 0x574f4c46) { 
            execl("/bin/sh", "sh", NULL); 
        }
    }
    return 0;
}
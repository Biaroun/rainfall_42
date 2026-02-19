#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void run(void)
{
    fwrite("Good... Wait what?\n", 1, 19, stdout);
    system("/bin/sh");
}

int main(void)
{
    char buf[64]; 
    return (0);
}

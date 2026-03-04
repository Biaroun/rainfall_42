#include <stdio.h>
#include <stdlib.h>

FILE *input;
FILE *output;
int m;

void v(void)
{
    char buf[520];
    fgets(buf, 512, input);
    printf(buf);

    if (m == 0x40)
    {
        fwrite("Wait what?!\n", 1, 12, output);
        system("/bin/sh");
    }
}

int main(void)
{
    v();
    return 0;
}
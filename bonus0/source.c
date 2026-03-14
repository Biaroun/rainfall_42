#include <unistd.h>
#include <stdio.h>
#include <string.h>

void p(char *dst, char *prompt)
{
    char buf[4096];

    puts(prompt);
    read(0, buf, 4096);
    *strchr(buf, '\n') = '\0';
    strncpy(dst, buf, 20);
}

void pp(char *dst)
{
    char first[20];
    char second[20];

    p(first, " - ");
    p(second, " - ");
    strcpy(dst, first);
    dst[strlen(dst)] = ' ';
    strcat(dst, second);
}

int main(void)
{
    char buf[42];

    pp(buf);
    puts(buf);
    return 0;
}

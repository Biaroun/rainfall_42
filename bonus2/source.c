#include <stdlib.h>
#include <string.h>

int language;

void greetuser(char *input)
{
    char buf[72];

    if (language == 1)
        strcpy(buf, "Hyvää päivää ");
    else if (language == 2)
        strcpy(buf, "Goedemiddag! ");
    else
        strcpy(buf, "Hello ");
    strcat(buf, input);
    puts(buf);
}

int main(int argc, char **argv)
{
    char    buf[76];
    char    *lang;

    if (argc != 3)
        return 1;

    memset(buf, 0, 76);
    strncpy(buf, argv[1], 40);
    strncpy(buf + 40, argv[2], 32);

    lang = getenv("LANG");
    if (lang)
    {
        if (memcmp(lang, "fi", 2) == 0)
            language = 1;
        else if (memcmp(lang, "nl", 2) == 0)
            language = 2;
    }

    greetuser(buf);
    return 0;
}

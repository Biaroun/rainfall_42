#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int ac, char **av)
{
    if (atoi(av[1]) == 423){
        char *args[] = {"/bin/sh", NULL};
        uid_t euid = geteuid();
        gid_t egid = getegid();

        setresgid(egid, egid, egid);
        setresuid(euid, euid, euid);

        execv("/bin/sh", args);
    } else {
        fwrite("No !\n", 1, 5, stderr);
    }
    return 0;
}

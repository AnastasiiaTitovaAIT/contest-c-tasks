#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char **argv)
{
    int st;
    if(!fork()) {
        if(!fork()) {
            execlp(argv[1], argv[1], NULL);
            exit(1);
        } else {
            wait(&st);
            if ((WIFEXITED(st) && WEXITSTATUS(st)) || WIFSIGNALED(st)) {
                execlp(argv[2], argv[2], NULL);
                exit(1);
            }
        }
    } else {
        wait(&st);
        if (WIFEXITED(st) && !WEXITSTATUS(st) && !WIFSIGNALED(st)) {
            if (!fork()) {
                execlp(argv[3], argv[3], NULL);
                exit(1);
            } else {
                wait(&st);
                if (WIFEXITED(st) && !WEXITSTATUS(st)) {
                    return 0;
                }
            }
        }
        return 1;
    }
}

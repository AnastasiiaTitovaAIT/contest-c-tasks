#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
int
main(int argc, char **argv)
{
    int fd[argc][2];
    for (int i = 1; i < argc; i++) {
        if (i != argc - 1) {
            pipe(fd[i]);
        }
        if (!fork()) {
            if (i != argc - 1) {
                dup2(fd[i][1], 1);
                close(fd[i][1]);
                close(fd[i][0]);
            }
            if (i != 1) {
                dup2(fd[i - 1][0], 0);
                close(fd[i - 1][0]);
            }
            execlp(argv[i], argv[i], NULL);
            exit(1);
        } else {
            if (i != argc - 1) {
                close(fd[i][1]);
            }
            if (i != 1) {
                close(fd[i - 1][0]);
            }
        }
    }
    for (int i = 1; i < argc; i++) {
        wait(NULL);
    }
    return 0;
}

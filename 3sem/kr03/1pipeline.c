#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char **argv)
{
    int st;
    int fd[2];
    pipe(fd);
    if(!fork()) {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        int fdf = open(argv[4], O_WRONLY | O_CREAT | O_APPEND, 0666);
        dup2(fdf, 1);
        close(fdf);
        if(!fork()) {
            execlp(argv[2], argv[2], NULL);
            exit(1);
        } else {
            wait(&st);
            if (WIFEXITED(st) && !WEXITSTATUS(st) && !WIFSIGNALED(st)) {
                if (!fork()) {
                    execlp(argv[3], argv[3], NULL);
                    exit(1);
                }
                wait(&st);
            }
        }
    } else {
        if (!fork()) {
            dup2(fd[1], 1);
            close(fd[1]);
            close(fd[0]);
            execlp(argv[1], argv[1], NULL);
            exit(1);
        }
        close(fd[1]);
        close(fd[0]);
        wait(&st);
        wait(&st);
        return 0;
    }
}

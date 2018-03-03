#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

enum { SIZE = 1024 };

int
main(int argc, char **argv)
{
    int n, g1, g2, nn, st;
    int numb = 0;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &g1);
    sscanf(argv[3], "%d", &g2);
    int fd[2];
    pipe(fd);
    for(int i = 1; i < n + 1; i++){
        if (!fork()){
            numb = i;
            continue;
        } else {
            break;
        }
    }
    if (numb == g1){
        close(fd[0]);
        char *buf = malloc(SIZE);
        int fdp = open(argv[4], O_RDONLY, 0777);
        while((nn = read(fdp, buf, SIZE)) > 0) {
            write(fd[1], buf, nn);
        }
        close(fdp);
        close(fd[1]);
        free(buf);
    } else if (numb == g2) {
        close(fd[1]);
        char *buf = malloc(SIZE);
        while((nn = read(fd[0], buf, SIZE)) > 0) {
            write(1, buf, nn);
        }
        close(fd[0]);
        free(buf);
    } else {
        close(fd[0]);
        close(fd[1]);
    }
    wait(&st);
    return 0;
}

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
    int st, max, f;
    int cur = 1;
    sscanf(argv[1], "%d", &max);
    if (max == 1) {
        printf("Done\n");
        fflush(stdout);
        return 0;
    }
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    if (fork()) {
        if (fork()) {
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);
            wait(&st);
            wait(&st);
            printf("Done\n");
            fflush(stdout);
            return 0;
        } else {
            close(fd2[1]);
            close(fd1[0]);
            f = dup(1);
            dup2(fd2[0], 0);
            close(fd2[0]);
            while(scanf("%d", &cur) > 0){
                printf("%d %d\n", 1, cur);
                fflush(stdout);
                cur++;
                if(cur == max) {
                    close(fd1[1]);
                    return 0;
                }
                dup2(fd1[1], 1);
                printf("%d\n", cur);
                fflush(stdout);
                dup2(f, 1);
            }
        }
    } else {
        close(fd1[1]);
        close(fd2[0]);
        f = dup(1);
        dup2(fd1[0], 0);
        close(fd1[0]);
        dup2(fd2[1], 1);
        printf("%d\n", cur);
        fflush(stdout);
        dup2(f, 1);
        while(scanf("%d", &cur) > 0) {
            printf("%d %d\n", 2, cur);
            fflush(stdout);
            cur++;
            if(cur == max) {
                close(fd2[1]);
                return 0;
            }
            dup2(fd2[1], 1);
            printf("%d\n", cur);
            fflush(stdout);
            dup2(f, 1);
        }
    }
}


#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
int max, fl, cur;
int main(int argc, char **argv)
{
    int st;
    cur++;
    sscanf(argv[1], "%d", &max);
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
            return 0;
        } else {
            FILE *fpr1 = fdopen(fd2[0], "r");
            FILE *fpw1 = fdopen(fd1[1], "w");
            close(fd2[1]);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            if (fl) {
                exit(0);
            }
            while(fscanf(fpr1, "%d", &cur) > 0){
                printf("%d %d\n", 1, cur);
                fflush(stdout);
                cur++;
                if(cur == max) {
                    fl = 1;
                    return 0;
                }
                fprintf(fpw1, "%d", cur);
                fflush(fpw1);
            }
        }
    } else {
        FILE *fpr = fdopen(fd1[0], "r");
        FILE *fpw = fdopen(fd2[1], "w");
        close(fd1[1]);
        close(fd2[0]);
        close(fd2[1]);
        close(fd1[0]);
        if (fl) {
            exit(0);
        }
        fprintf(fpw, "%d\n", cur);
        fflush(fpw);
        while(fscanf(fpr, "%d", &cur) > 0){
            printf("%d %d\n", 2, cur);
            fflush(stdout);
            cur++;
            if(cur == max) {
                fl = 1;
                exit(0);
            }
            fprintf(fpw, "%d\n", cur);
            fflush(fpw);
        }
    }
}


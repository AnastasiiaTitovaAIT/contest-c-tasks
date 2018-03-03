#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void f1(int s);
void f2 (int s);
int chpid[2];
int fd[2];
int fstd, cur, max;

int
main(int argc, char **argv)
{
    int st;
    cur++;
    sscanf(argv[1], "%d", &max);
    if (max == 1) {
        printf("Done\n");
        fflush(stdout);
        return 0;
    }
    pipe(fd);
    if (fork()) {
        if (fork()) {
            close(fd[0]);
            close(fd[1]);
            wait(&st);
            wait(&st);
            printf("Done\n");
            fflush(stdout);
            return 0;
        } else {
            signal(SIGUSR1, f1);
            chpid[0] = getpid();
            fstd = dup(1);
            dup2(fd[0], 0);
            close(fd[0]);
            while(1);
        }
    } else {
        signal(SIGUSR2, f2);
        chpid[1] = getpid();
        printf("Done1\n");
        fstd = dup(1);
        dup2(fd[0], 0);
        close(fd[0]);
        dup2(fd[1], 1);
        printf("%d\n", cur);
        fflush(stdout);
        dup2(fstd, 1);
        printf("Done2\n");
        if(!chpid[0]){
            usleep(1);
        }
        kill(chpid[0], SIGUSR1);
         printf("Done3\n");
        while(1);
    }
}
void
f1 (int sig)
{
    signal(SIGUSR1, f1);
    signal(SIGUSR2, f2);
    int numb = 1;
    if (scanf("%d\n", &cur) > 0) {
        printf("1 %d", cur);
        fflush(stdout);
        cur++;
        if(cur == max) {
            close(fd[1]);
            kill(0, SIGTERM);
        }
        dup2(fd[1], 1);
        printf("%d\n", cur);
        fflush(stdout);
        dup2(fstd, 1);
        kill(chpid[1], SIGUSR2);
    } else {
        kill(0, SIGTERM);
    }
}
void
f2 (int sig)
{
    signal(SIGUSR1, f1);
    signal(SIGUSR2, f2);
    int numb = 1;
    // printf("Done4 %d\n", getpid());
    if (scanf("%d\n", &cur) > 0) {
        printf("2 %d", cur);
        fflush(stdout);
        cur++;
        if(cur == max) {
            close(fd[1]);
            kill(0, SIGTERM);
        }
        dup2(fd[1], 1);
        printf("%d\n", cur);
        fflush(stdout);
        dup2(fstd, 1);
        kill(chpid[0], SIGUSR1);
    } else {
        kill(0, SIGTERM);
    }
}

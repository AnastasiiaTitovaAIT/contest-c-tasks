#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

enum { SLEEPTIM = 1000};
void f (int s);
int fd[2];
int chp[2];
int fl;

int
main(int argc, char **argv)
{
    int target, fstd, cur, max, st;
    int mynum = 0;
    sscanf(argv[1], "%d", &max);
    if (max == 1) {
        printf("Done\n");
        fflush(stdout);
        return 0;
    }
    pipe(fd);
    fstd = dup(1);
    for(int i = 0; i < 2; i++) {
        if(!fork()) {
            mynum = i + 1;
            chp[i] = getpid();
        }
    }
    if (mynum) {
        signal(SIGUSR1, f);
        dup2(fd[0], 0);
        close(fd[0]);
        if(mynum == 2){
            dup2(fd[1], 1);
            printf("%d\n", 1);
            fflush(stdout);
            dup2(fstd, 1);
            printf("yere %d\n", mynum);
            kill(target, SIGUSR1);
        }
        while(1) {
           // printf("%d\n", mynum);
            while(!fl) {
                usleep(SLEEPTIM);
                //printf("вунерева, вунерева\n");
            }
            fl = 0;
            scanf("%d", &cur);
            printf("%d %d\n", mynum, cur);
            cur++;
            if (cur == max) {
                fl = 2;
                kill(target, SIGUSR1);
                close(fd[1]);
                exit(0);
            }
            dup2(fd[1], 1);
            printf("%d\n", cur);
            fflush(stdout);
            dup2(fstd, 1);
            kill(target, SIGUSR1);
        }
    } else {
        close(fd[0]);
        close(fd[1]);
        wait(&st);
        wait(&st);
        printf("Done1\n");
        fflush(stdout);
        return 0;
    }
}

void f (int sig)
{
    signal(SIGUSR1, f);
  //fprintf(stdout, "it's handler\n");
    if(fl == 2) {
        close(fd[1]);
        exit(0);
    }
    fl = 1;
}


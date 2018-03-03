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
    int target, fstd, mynum, cur, max, st;
    sscanf(argv[1], "%d", &max);
    if (max == 1) {
        printf("Done\n");
        fflush(stdout);
        return 0;
    }
    pipe(fd);
    fstd = dup(1);
    for(int i = 0; i < 2; i++) {
        dup2(fd[0], 0);
        close(fd[0]);
        if(!fork()) {
            signal(SIGUSR1, f);
            chp[i] = getpid();
            mynum = i + 1;
            if (i == 0) {
                while(!fl){
                    usleep(SLEEPTIM);
                }
                fl = 0;
                scanf("%d", &target);
                dup2(fd[1], 1);
                printf("%d\n", 1);
                fflush(stdout);
                dup2(fstd, 1);
                kill(target, SIGUSR1);
            } else {
                target = chp[0];
                dup2(fd[1], 1);
                printf("%d\n", getpid());
                fflush(stdout);
                dup2(fstd, 1);
                kill(target, SIGUSR1);
            }
            while(1) {
                while(!fl) {
                    usleep(SLEEPTIM);
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
        }
        close(fd[1]);
        wait(&st);
        wait(&st);
        printf("Done\n");
        fflush(stdout);
        return 0;
    }
}

void f (int sig)
{
    signal(SIGUSR1, f);
    if(fl == 2) {
        close(fd[1]);
        exit(0);
    }
    fl = 1;
}

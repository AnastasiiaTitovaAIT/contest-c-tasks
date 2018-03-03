#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

enum { SLEEPTIM = 1000};
void f1 (int s);
void f2 (int s);
int fd[2];
int chp[2];
int fl1, fl2;
int main(int argc, char **argv)
{
    int target, cur, max, std;
    sscanf(argv[1], "%d", &max);
    pipe(fd);
    if (max == 1) {
        printf("Done\n");
        fflush(stdout);
        return 0;
    }
    pipe(fd);
    fstd = dup(1);
    if(!fork()) {
        dup2(fd[0], 0);
        close(fd[0]);
        signal(SIGUSR1, f1);
        chp[0] = getpid();
        while(!fl1){
            usleep(SLEEPTIM);
        }
        fl1 = 0;
        scanf("%d", &target);
        std = dup(1);
        while(1) {
            while(!fl1){
                usleep(SLEEPTIM);
            }
            fl1 = 0;
            scanf("%d", &cur);
            printf("1 %d\n", cur);
            fflush(stdout);
            cur++;
            if(cur == max) {
                close(fd[1]);
                fl2 = 2;
                return 0;
            }
            dup2(fd[1], 1);
            printf("%d\n", cur);
            fflush(stdout);
        }
    }
}

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void f1(int s);
void f2(int s);
void f3(int s);
int fdp, max;
int targ[2];
int fd[2];

int
main(int argc, char **argv)
{
    signal(SIGUSR1, f1);
    int st;
    sscanf(argv[1], "%d", &max);
    pipe(fd);
    dup2(fd[0], 0);
    close(fd[0]);
    if(!fork()) {//son 1
        signal(SIGUSR1, f1);
        signal(SIGUSR2, f2);
        signal(SIGTERM, f3);
        printf("son1\n");
        while(1);
    } else {
        if (!fork()) {//son 2
            signal(SIGUSR1, f1);
            signal(SIGUSR2, SIG_IGN);
            signal(SIGTERM, f3);
            fdp = dup(1);
            dup2(fd[1], 1);
            printf("son2\n");
            printf("%d\n", getpid());
            fflush(stdout);
            dup2(fdp, 1);
            kill(0, SIGUSR2);
            printf("son2aftrsig\n");
            while(1);
        } else { //father
            signal(SIGUSR2, SIG_IGN);
            signal(SIGTERM, SIG_IGN);
            close(fd[1]);
            wait(&st);
            wait(&st);
            printf("Done\n");
            fflush(stdout);
            return 0;
        }
    }
}
void
f1(int sig)
{
    signal(SIGUSR1, f1);
    int cur, fl;
    static int cnt = 0;
    if(!cnt) {
        cnt++;
        if(cnt == max) {
            kill(0, SIGTERM);
        }
        dup2(fd[1], 1);
        printf("%d\n", cnt);
        fflush(stdout);
        dup2(fdp, 1);
        fl = (cnt % 2)?1:2;
        kill(targ[fl - 1], SIGUSR1);
        return;
    }
    cnt++;
    if(cnt == max) {
        kill(0, SIGTERM);
    } else {
        scanf("%d", &cur);
        fl = (cur % 2)?1:2;
        printf("son\n");
        printf("%d %d\n", fl, cur);
        fflush(stdout);
        dup2(fd[1], 1);
        printf("%d\n", cnt);
        fflush(stdout);
        dup2(fdp, 1);
        kill(targ[fl - 1], SIGUSR1);
    }
}
void
f2(int sig)
{
    scanf("%d", &targ[0]);
    printf("She's got the look\n");
    targ[1] = getpid();
    kill(targ[0], SIGUSR1);
}
void
f3(int sig)
{
    close(fd[1]);
    exit(0);
}

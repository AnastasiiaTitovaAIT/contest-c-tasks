#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
int mod = 0;
void
f1 (int sig)
{
    if (sig == SIGUSR1) {
        mod = 0;
    } else if (sig == SIGUSR2) {
        mod = 1;
    }
    return ;
}
int
main(void)
{
    signal(SIGUSR1, f1);
    signal(SIGUSR2, f1);
    int x;
    printf("%d\n", getpid());
    fflush(stdout);
    while (scanf("%d", &x) > 0) {
        if (mod) {
            printf("%d\n", x*x);
            fflush(stdout);
        } else {
            printf("%d\n", -x);
            fflush(stdout);
        }
    }
    return 0;
}

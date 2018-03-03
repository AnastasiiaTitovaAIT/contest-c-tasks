#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <math.h>

void f(int sig)
{
    printf("-1\n");
    fflush(stdout);
    exit(0);
}

int main(int argc, char **argv)
{
    signal(SIGALRM, f);
    long long time, cur;
    sscanf(argv[1], "%lld", &time);
    alarm(time);
    scanf("%lld", &cur);
    while(cur != 0) {
        printf("%lld\n", cur*cur);
        fflush(stdout);
        scanf("%lld", &cur);
    }
    return 0;
}

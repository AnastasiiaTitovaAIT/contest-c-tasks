#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <math.h>
volatile int cur;
void
f (int sig)
{
    signal(SIGINT, f);
    static int cn = 0;
    if (sig == SIGINT) {
        cn++;
    }
    if (cn == 4 || sig == SIGTERM) {
        exit(0);
    }
    printf("%d\n", cur);
    fflush(stdout);
}

int
main(void)
{
    signal(SIGINT, f);
    signal(SIGTERM, f);
    int low, high;
    int div = 0;
    scanf("%d", &low);
    scanf("%d", &high);
    printf("%d\n", getpid());
    fflush(stdout);
    for (int i = low; i < high; i++) {
        for (int j = 2; j < i; j++) {
            if (j > ((sqrt(i)) + 1)) {
                cur = i;
                break;
            }
            if (i % j == 0) {
                div += 1;
                break;
            }
        }
        if (!div && i > 1) {
            cur = i;
        } else {
            div = 0;
        }
    }
    printf("%d\n", -1);
    fflush(stdout);
    return 0;
}

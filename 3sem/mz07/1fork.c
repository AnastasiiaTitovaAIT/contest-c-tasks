#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(void)
{
    int  st, a;
    while (scanf("%d", &a) != EOF) {
        switch(fork())
        {
        case -1:
            exit(1);
        case 0:
            break;
        default:
            wait(&st);
            printf("%d\n", a);
            return 0;
        }
    }
    return 0;
}

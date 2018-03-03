#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
int main(void)
{
    printf("1");
    int st;
    fflush(stdout);
    if (!fork()) {
        printf("2");
    }
    wait(&st);
    fflush(stdout);
    printf("3");
    return 0;
}

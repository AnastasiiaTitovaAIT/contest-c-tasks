#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
int
main(void)
{
    int fd[2];
    int st;
    time_t timer;
    pipe(fd);
    timer = time(NULL);
    write(fd[1], &timer, sizeof(timer));
    write(fd[1], &timer, sizeof(timer));
    write(fd[1], &timer, sizeof(timer));
    close(fd[1]);
    if (!fork()) {
        read(fd[0], &timer, sizeof(timer));
        struct tm *t = localtime(&timer);
        if (!fork()) {
            if (!fork()) {
                read(fd[0], &timer, sizeof(timer));
                t = localtime(&timer);
                printf("S:%.2d\n", t->tm_sec);
            } else {
                read(fd[0], &timer, sizeof(timer));
                t = localtime(&timer);
                wait(&st);
                printf("M:%.2d\n", t->tm_min);
            }
        } else {
            read(fd[0], &timer, sizeof(timer));
            t = localtime(&timer);
            wait(&st);
            printf("H:%.2d\n", t->tm_hour);
        }
    }
    close(fd[0]);
    wait(&st);
    return 0;
}

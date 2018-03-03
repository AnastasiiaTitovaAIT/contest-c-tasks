#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
int max, fl, cur;
int
main(int argc, char **argv)
{
    int st;
    sscanf(argv[1], "%d", &max);
    int fd1[2];
    int fd2[2];
    cur++;
    pipe(fd1);
    pipe(fd2);
    if (fork()) {
        if (fork()) {
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);
            wait(&st);
            wait(&st);
            printf("Done\n");
            return 0;
        } else {
            close(fd2[1]);
            close(fd1[0]);
            if (fl) {
                return 0;
            }
            while(read(fd2[0], &cur, sizeof(cur)) > 0){
                printf("%d %d\n", 1, cur);
                cur++;
                if(cur == max) {
                    fl = 1;
                    return 0;
                }
                write(fd1[1], &cur, sizeof(cur));
            }
        }
    } else {
        close(fd1[1]);
        close(fd2[0]);
        if (fl) {
            return 0;
        }
        write(fd2[1], &cur, sizeof(cur));
        while(read(fd1[0], &cur, sizeof(cur)) > 0){
            printf("%d %d\n", 2, cur);
            cur++;
            if(cur == max) {
                fl = 1;
                return 0;
            }
            write(fd2[1], &cur, sizeof(cur));
        }
    }
}


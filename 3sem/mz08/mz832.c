#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int max, fl;
int
main(int argc, char **argv)
{
    int st, cnt, cur;
    sscanf(argv[1], "%d", &max);
    cnt = 1;
    int fd[2];
    pipe(fd);
    FILE *pout = fdopen(1, "w");
    printf("Done\n");
    if (fork()) {
        if (fork()) {
            printf("Done1\n");
            close(fd[0]);
            close(fd[1]);
            while(wait(&st) == -1);
            printf("Done\n");
            return 0;
        } else {
            dup2(fd[0], 0);
            printf("Done3\n");
            dup2(fd[1], 1);
            printf("Done4\n");
            close(fd[0]);
            close(fd[1]);
            printf("Done2\n");
            if (fl) {
                return 0;
            }
            while(1) {
                printf("Done\n");
                scanf("%d", &cur);
                printf("Done\n");
                fflush(stdin);
                printf("Done\n");
                //read(fd[0], &cur, sizeof(cur));
                printf("Done\n");
                fprintf(pout,"%d %d\n", 1, cur);
                printf("Done\n");
                fflush(pout);
                printf("Done\n");
                cnt++;
                if(cnt == max) {
                    fl = 1;
                    fclose(pout);
                    return 0;
                }
                //write(fd[1], &cnt, sizeof(cnt));
                printf("%d", cnt);
                fflush(stdout);
                sleep(2);
            }
        }
    } else {
        printf("Done\n");
        dup2(fd[0], 0);
        printf("Done\n");
        dup2(fd[1], 1);
        printf("Done\n");
        close(fd[0]);
        printf("Done\n");
        close(fd[1]);
        printf("Done\n");
        if (fl) {
            fclose(pout);
            return 0;
        }
        printf("%d", cnt);
        fflush(stdout);
        //write(fd[1], &cnt, sizeof(cnt));
        sleep(1);
        while(1) {
            //read(fd[0], &cur, sizeof(cur));
            scanf("%d", &cur);
            fflush(stdin);
            fprintf(pout, "%d %d\n", 2, cur);
            fflush(pout);
            //write(fd[1], &cnt, sizeof(cnt));
            printf("%d", cnt);
            fflush(stdout);
            sleep(1);
        }
    }
}


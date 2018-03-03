#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

enum { SIZE = 1024 };

int
main(int argc, char **argv)
{
    int n, g1, g2;
    int count = 0;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &g1);
    sscanf(argv[3], "%d", &g2);
    int fd[2];
    pipe(fd);
    if(!fork()){
        for(int i = 1; i < n -1; i++){
         if (i == g1 - 1){
                    printf("here %d", i);
                    fflush(stdout);
                close(fd[0]);
                FILE *fp = fopen(argv[4], "r");
                while(fp) {
                    write(fd[1], fp, SIZE);
                }
                fclose(fp);
                close(fd);
            } else if(i == g2 - 1) {
                close(fd[1]);
                char *buf = calloc(1, SIZE);
                while(read(fd[0], buf, SIZE) > 0) {
                    printf("%s", buf);
                }
                close(fd[1]);
            } else {
                close(fd[0]);
                close(fd[1]);
            }
    }
}

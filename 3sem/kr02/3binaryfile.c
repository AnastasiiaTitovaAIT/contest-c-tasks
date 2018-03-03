#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>
int
main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);
    unsigned short n;
    double mult = 1.0;
    double *x = calloc(1, sizeof(*x));
    size_t d = sizeof(*x);
    size_t sh = sizeof(n);
    lseek(fd, 0, SEEK_END);
    while(lseek(fd, -sh, SEEK_CUR) >= 0) {
        read(fd, &n, sh);
        if (!n){
            printf("%d\n", 0);
            lseek(fd, -sh, SEEK_CUR);
            continue;
        }
        x = realloc(x, n * d);
        long offset = lseek(fd, -(sh + n * d), SEEK_CUR);
        read(fd, x, n * d);
        for (int i = 0; i < n; i++) {
            mult *= pow(x[i], 1.0/n);
        }
        printf("%.10g\n", mult);
        mult = 1.0;
        lseek(fd, offset, SEEK_SET);
    }
    free(x);
    close(fd);
    return 0;
}

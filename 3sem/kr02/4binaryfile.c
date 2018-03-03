#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>
int
main(int argc, char **argv)
{
    int numb, a0, d, k, st;
    sscanf(argv[1], "%d", &numb);
    sscanf(argv[3], "%d", &a0);
    sscanf(argv[4], "%d", &d);
    sscanf(argv[5], "%d", &k);
    int fd = creat(argv[2], 0777);
    int fdi;
    for(int i = 0; i < numb; i++) {
        switch(fork())
        {
        case 0:
            fdi = open(argv[2], O_WRONLY);
            for(int j = 0; j < k; j++) {
                lseek(fdi, (numb * j + i) * sizeof(a0), 0);
                int c = a0 + d * (numb * j + i);
                write(fdi, &c, sizeof(a0));
            }
            close(fdi);
            return 0;
            break;
        default:
        {
        }
        }
    }
    while(wait(&st) != -1) {
    }
    close(fd);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
int
main(int argc, char **argv)
{
    int i = 0;
    int port;
    sscanf(argv[1], "%d", &port);
    int *buf = calloc(port, sizeof(*buf));
    while(scanf("%d", &buf[i % port]) == 1) {
        i++;
    }
    if (i > port) {
        for (int j = i % port; j < port; j++) {
            printf("%d\n", buf[j]);
        }
        i %= port;
    }
    for (int j = 0; j < i; j++){
        printf("%d\n", buf[j]);
    }
    return 0;
}

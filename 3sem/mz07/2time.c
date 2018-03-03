#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int
main(int argc, char **argv)
{
    int r_time, w_time, wr_time;
    sscanf(argv[1], "%d", &r_time);
    sscanf(argv[2], "%d", &w_time);
    sscanf(argv[3], "%d", &wr_time);
    char str[PATH_MAX];
    int fl = 0;
    int time = 0;
    while(fgets(str, PATH_MAX, stdin)) {
        char inf[2];
        int addr_p, addr_c;
        sscanf(str, "%c%c %x", &inf[0], &inf[1], &addr_c);
        if (inf[0] == 'R') {
            if (fl && addr_p == addr_c) {
                time -= (w_time - wr_time);
            } else {
                time += r_time;
            }
            fl = 0;
        }
        if (inf[0] == 'W') {
            time += w_time;
            fl = 1;
        }
        addr_p = addr_c;
    }
    printf("%d\n", time);
    return 0;
}

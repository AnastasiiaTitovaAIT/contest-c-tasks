#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int
main(int argc, char **argv)
{
    int year, mday, wday;
    int count = 0;
    sscanf(argv[1], "%d", &year);
    sscanf(argv[2], "%d", &mday);
    sscanf(argv[3], "%d", &wday);
    if(wday == 7) {
        wday = 0;
    }
    struct tm t;
    memset(&t, 0, sizeof(t));
    t.tm_mday = mday;
    t.tm_year = year - 1900;
    for(int i = 0; i < 11; i++){
        t.tm_mon = i;
        mktime(&t);
        if(t.tm_wday == wday) {
            count ++;
        }
        t.tm_wday = 0;
    }
    printf("%d", count);
    return 0;
}

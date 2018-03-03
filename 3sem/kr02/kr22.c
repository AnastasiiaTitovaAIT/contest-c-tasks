#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
enum
{
    YEAR_OFF = 1900,
    LASTWDAY = 7,
    MON = 12
};
int
main(int argc, char **argv)
{
    int year, mday, wday;
    int count = 0;
    sscanf(argv[1], "%d", &year);
    sscanf(argv[2], "%d", &mday);
    sscanf(argv[3], "%d", &wday);
    if(wday == LASTWDAY) {
        wday = 0;
    }
    struct tm t;
    memset(&t, 0, sizeof(t));
    t.tm_year = year - YEAR_OFF;
    for(int i = 0; i < MON; i++){
        t.tm_mday = mday;
        t.tm_mon = i;
        mktime(&t);
        if(t.tm_wday == wday && t.tm_mday == mday) {
            count ++;
        }
        t.tm_wday = 0;
    }
    printf("%d\n", count);
    return 0;
}

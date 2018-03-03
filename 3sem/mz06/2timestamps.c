#include<stdio.h>
#include<time.h>
#include<limits.h>
#include<string.h>
enum { BUF_SIZ = 1001 };
int
main(int argc, char **argv)
{
    char name[PATH_MAX];
    strcpy(name, argv[1]);
    long long prev, cur;
    FILE *fd = fopen(name, "r");
    int year, mon, day, hr, min, sec;
    char str[BUF_SIZ];
    fgets(str, BUF_SIZ, fd);
    struct tm t;
    memset(&t, 0, sizeof(t));
    sscanf(str, "%d/%d/%d%d:%d:%d", &year, &mon, &t.tm_mday, &t.tm_hour, &t.tm_min, &t.tm_sec);
    t.tm_year = year - 1900;
    t.tm_mon = mon - 1;
    t.tm_isdst = -1;
    prev = mktime(&t);
    while (fgets(str, BUF_SIZ, fd) != NULL) {
        sscanf(str, "%d/%d/%d%d:%d:%d", &year, &mon, &day, &hr, &min, &sec);
        memset(&t, 0, sizeof(t));
        t.tm_year = year - 1900;
        t.tm_mon = mon - 1;
        t.tm_mday = day;
        t.tm_hour = hr;
        t.tm_min = min;
        t.tm_sec = sec;
        t.tm_isdst = -1;
        cur = mktime(&t);
        printf("%lld\n", cur - prev);
        prev = cur;
    }
    return 0;
}

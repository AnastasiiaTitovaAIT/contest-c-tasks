#include <stdio.h>
#include <limits.h>
int
main(void)
{
    char str[PATH_MAX];
    int sum = 0;
    while(fgets(str, PATH_MAX, stdin) != NULL){
        int prev, next;
        sscanf(str, "%x-%x", &prev, &next);
        sum += next - prev;
    }
    printf("%u", sum);
    return 0;
}

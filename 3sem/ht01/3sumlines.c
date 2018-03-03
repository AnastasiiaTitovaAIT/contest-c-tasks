#include<stdio.h>
#include<stdlib.h>
#include<string.h>
enum { SIZE_BUF = 3 };
char
*getline2(FILE *f)
{
    size_t t = sizeof(char);
    int c, j;
    int lens = 0;
    char *str = calloc(SIZE_BUF, t);
    j = SIZE_BUF;
    while ((c = getc(f)) != EOF) {
        str[lens] = c;
        lens++;
        if (str[lens - 1] == '\n') {
            break;
        }
        if (lens == j) {
            j *= SIZE_BUF;
            str = realloc(str, j * t);
        }
    }
    if (c == EOF && lens == 0){
        free(str);
        return NULL;
    }
    if (lens == j) {
        str = realloc(str, j * SIZE_BUF * t);
    }
    str[lens] = '\0';
    return str;
}
int
main(void)
{
    int i, nn;
    int flag = 0;
    double sum, cur;
    char *str = NULL;
    while ((str = getline2(stdin)) != NULL) {
        sum = 0;
        i = 0;
        nn = 0;
        while(sscanf(str + i, "%lf%n", &cur, &nn) == 1) {
            flag = 1;
            sum += cur;
            i += nn;
        }
        if (flag) {
            printf("%.10g\n", sum);
            flag = 0;
        } else {
            printf("nan\n");
        }
        free(str);
    }
    return 0;
}

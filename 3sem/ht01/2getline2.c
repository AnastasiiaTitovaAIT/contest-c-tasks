#include<stdio.h>
#include<stdlib.h>
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

#include<stdio.h>
#include<string.h>
#include<limits.h>
int
main(int argc, char **argv)
{
    long long str_len = 0;
    double sum_doub = 0;
    int numb = 0;
    long long sum_int = 0;
    int x_i;
    double x_d;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == 'i') {
            sscanf(argv[i] + 1, "%d", &x_i);
            sum_int += x_i;
        } else if(argv[i][0] == 'd') {
            sscanf(argv[i] + 1, "%lf", &x_d);
            sum_doub += x_d;
            numb ++;
        } else {
            str_len += strlen(argv[i]);
        }
    }
    if (numb) {
        sum_doub /= numb;
    }
    printf("%.10g\n%lld\n%lld\n", sum_doub, sum_int,  str_len);
    return 0;
}

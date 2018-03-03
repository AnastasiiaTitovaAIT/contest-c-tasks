/*В аргументах командной стрки остаток на счете, депозитный и кредитный процент
и дальше в них передаются суммы, которые снимают/кладут на счет.*/
#include<stdio.h>
#include<float.h>
int
main(int argc, char **argv)
{
    double total, depos, cred, change;
    sscanf(argv[1], "%lf", &total);
    sscanf(argv[2], "%lf", &depos);
    sscanf(argv[3], "%lf", &cred);
    for (int i = 4; i < argc; i++){
        sscanf(argv[i], "%lf", &change);
        total += change;
        if (total > DBL_EPSILON){
            total *= (1 + depos / 100);
        } else {
            total *= (1 + cred / 100);
        }
    }
    printf("%.10g\n", total);
    return 0;
}

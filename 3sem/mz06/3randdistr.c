#include<stdio.h>
#include<stdlib.h>
int
main(void)
{
    int n, m, seed, r;
    scanf("%d", &n);
    int *var = calloc(n, sizeof(*var));
    int *set = calloc(n, sizeof(*set));
    scanf("%d%d", var, set);
    for (int i = 1; i < n; i++) {
        scanf("%d %d", var + i, set + i);
        set[i] += set[i - 1];
    }
    scanf("%d %d", &m, &seed);
    srand(seed);
    for(int j = 0; j < m; j++) {
        r = rand()/(RAND_MAX + 1.0) * 100;
        for (int i = 0; i < n; i++) {
            if (r < set[i]) {
                printf("%d\n", var[i]);
                break;
            }
        }
    }
    free(var);
    free(set);
    return 0;
}



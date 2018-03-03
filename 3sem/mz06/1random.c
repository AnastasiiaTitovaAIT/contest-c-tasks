#include<stdio.h>
#include<stdlib.h>
int
main(int argc, char **argv)
{
    unsigned int count, seed;
    int low, high, result;
    sscanf(argv[1],"%u", &count);
    sscanf(argv[2],"%d", &low);
    sscanf(argv[3],"%d", &high);
    sscanf(argv[4],"%u", &seed);
    srand(seed);
    for (int i = 0; i < count; i++) {
        result = rand()/(RAND_MAX * 1.0) * (high - low) + low;
        printf("%d\n", result);
    }
    return 0;
}

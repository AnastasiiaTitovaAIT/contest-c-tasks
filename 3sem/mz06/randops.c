#include <stdio.h>
#include <stdlib.h>
enum
{
    INC = 12345,
    MOD = 1 << 31,
    MULT = 1103515245
};
struct RandomOperations;
typedef struct RandomGenerator
{
    struct RandomOperations *ops;
    int value;
}RandomGenerator;
typedef struct RandomOperations
{
    void (*destroy)(RandomGenerator *);
    int (*next)(RandomGenerator *);
}RandomOperations;
int
next(RandomGenerator *rr)
{
    rr->value = ((long long int)((long long int)(rr->value) * MULT) + INC) % MOD;
    return rr->value;
}
void
destroy(RandomGenerator *rr)
{
    free(rr);
    return;
}
RandomOperations op = 
{ 
    destroy, 
    next 
};
RandomGenerator
*random_create(int seed)
{
    RandomGenerator *rr = calloc(1, sizeof(*rr));
    rr->ops = &op;
    rr->value = seed;
    return rr;
}

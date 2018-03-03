#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
int
main(int argc, char **argv)
{
    int memory_size, cashe_size, block_size;
    sscanf(argv[1], "%d", &memory_size);
    sscanf(argv[2], "%d", &cashe_size);
    sscanf(argv[3], "%d", &block_size);
    int mb, block_count, cb;
    block_count = cashe_size / block_size;
    int *flags = calloc(block_count, sizeof(*flags));
    memset(flags, -1, block_count * sizeof(*flags));
    char str[PATH_MAX];
    int slip = 0;
    while(fgets(str, PATH_MAX, stdin)) {
        char inf[2];
        int addr;
        sscanf(str, "%c%c %x", &inf[0], &inf[1], &addr);
        mb = addr / block_size;
        cb = mb % block_count;
        if (flags[cb] != -1 && flags[cb] != mb) {
            slip++;
        }
        flags[cb] = mb;
    }
    free(flags);
    printf("%d\n", slip);
    return 0;
}

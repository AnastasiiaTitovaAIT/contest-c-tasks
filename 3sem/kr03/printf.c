#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("in.bin", O_RDWR, 0777);
    int x = 0;
    FILE *fp = fopen("sort.txt", "w");
    while(read(fd, &x, sizeof(x)) > 0)
    {
        fprintf(fp, "%d ", x);
    }
    close(fd);
    fclose(fp);
    return 0;
}


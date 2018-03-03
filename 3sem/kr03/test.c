#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("in.bin", O_RDWR | O_TRUNC, 0777);
    int x = 0;
    for(int i = 40; i >= 0; i--)
    {
        x = rand()/(RAND_MAX + 1.0) * i;
        write(fd, &x, sizeof(x));
    }
    lseek(fd, 0, SEEK_SET);
    FILE *fp = fopen("array.txt", "w");
    while(read(fd, &x, sizeof(x)) > 0)
    {
        fprintf(fp, "%d ", x);
    }
    close(fd);
    fclose(fp);
    return 0;
}

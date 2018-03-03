#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int
main(int argc, char **argv)
{
    long long cur_offset, x;
    unsigned short data_size;
    int sum_size = 0;
    int amnt = 0;
    sscanf(argv[2], "%lld", &cur_offset);
    int fd = open(argv[1], O_RDONLY);
    if (lseek(fd, 0, SEEK_END)) {
        while(1) {
            lseek(fd, cur_offset, SEEK_SET);
            read(fd, &data_size, sizeof(data_size));
            lseek(fd, data_size, SEEK_CUR);
            sum_size += (int)data_size;
            amnt++;
            read(fd, &x, sizeof(x));
            if (!x) {
                break;
            }
            cur_offset += x;
        }
    }
    printf("%d\n%d\n", amnt, sum_size);
    close(fd);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
enum
{ SIZE = 32 };
int
main(int argc, char **argv)
{
    int nn = SIZE;
    int t = sizeof(nn);
    int fd = open("in.bin", O_RDWR, 0777);
    int *arr = calloc(SIZE, t);
    long long s = lseek(fd, 0, SEEK_END);
    s /= t;
    for(int i = s - 1; i >= 0; i--) {
        lseek(fd, 0, SEEK_SET);
        for(int j = 0; j < i; j++) {
            if(j % SIZE == 0) {
                if (j) {
                    lseek(fd, -nn * t, SEEK_CUR);
                    write(fd, arr, t * nn);
                    lseek(fd, -t, SEEK_CUR);
                }
                nn = read(fd, arr, SIZE * t);
            }
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    lseek(fd, -(nn + 1) * t, SEEK_CUR);
    write(fd, arr, t * (nn + 1));
   // free(arr);
    close(fd);
    return 0;
}


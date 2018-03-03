#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
enum
{
    LEFT = 1,
    RIGHT,
    ELEM
};
void
my_read(int fd, void *buf, int t)
{
    int nr;
    char *p = buf;
    while (t) {
        nr = read(fd, p, t);
        t -= nr;
        p += nr;
    }
    return;
}
void
traversal (int curr_elm, int fd, size_t t)
{
    int nxt_elm, key;
    lseek(fd, t * (curr_elm * ELEM + RIGHT), 0);
    my_read(fd, &nxt_elm, t);
    if(nxt_elm){
        traversal(nxt_elm, fd, t);
    }
    lseek(fd, t * (curr_elm * ELEM), 0);
    my_read(fd, &key, t);
    printf("%d\n", key);
    lseek(fd, t * (curr_elm * ELEM + LEFT), 0);
    my_read(fd, &nxt_elm, t);
    if (nxt_elm) {
        traversal(nxt_elm, fd, t);
    }
    return;
}
int
main(int argc, char **argv)
{
    int t = sizeof(int);
    int fd = open(argv[1], O_RDONLY);
    traversal(0, fd, t);
    close(fd);
    return 0;
}

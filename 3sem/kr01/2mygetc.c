#include<stdio.h>
#include<stdlib.h>
struct MyFile
{
    int fd;//файловый дескриптор для чтения
    int size; //размер буфера
    char *buf;//указатель на буфер
    int out;//указатель на выходящий символ
    int nn; //указатель на последний в буфере
};
int
mygetc(struct MyFile *f)
{
    unsigned char ret_c;
    if (f->out < f->nn) {
        ret_c = f->buf[f->out++];
        return ret_c;
    } else {
        f->out  = 0;
        if (!(f->nn = read(f->fd, f->buf, f->size))) {
            f->nn = 0;
            return EOF;
        }
        ret_c = f->buf[f->out++];
        return ret_c;
    }
}

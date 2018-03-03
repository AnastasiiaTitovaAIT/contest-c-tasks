#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
enum
{
    DEC = 10,
    BUFF_SIZE = 16
};
int
main(void)
{
    long long sum = 0;
    int temp = 0;
    int flag_min = 0;
    int flag_space = 0;
    int nr;
    char buf[BUFF_SIZE];
    while ((nr = read(0, buf, BUFF_SIZE)) > 0) {
        for (int i = 0; i < nr; i++) {
            if(isspace(buf[i])){
                if (!flag_space) {
                    if (flag_min){
                        temp = -temp;
                        flag_min = 0;
                    }
                    sum += temp;
                    temp = 0;
                    flag_space = 1;
                }
            } else {
                if (buf[i] == '-'){
                    flag_min = 1;
                    flag_space = 0;
                } else {
                    if(buf[i] != '+'){
                        temp = temp * DEC + (buf[i] - '0');
                        flag_space = 0;
                    }
                }
            }
        }
    }
    if (!nr) {
        if (flag_min == 1) {
            temp = -temp;
        }
        sum += temp;
    }
    printf("%lld\n", sum);
    return 0;
}

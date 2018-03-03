#include<stdio.h>
#include<string.h>
enum
{
    R_OFF = 8,
    W_OFF = 7,
    X_OFF = 6,
    BLOCK_SIZE = 3
};
int
parse_rwx_permissions(const char *str)
{
    if (!str) {
        return -1;
    }
    if (strlen(str) != 9) {
        return -1;
    }
    int res = 0;
    for (int i = 0; i < 3; i++){
        int j = i * BLOCK_SIZE;
        if (str[j] == 'r') {
            res += 1 << (R_OFF - j);
        } else if (str[j] != '-') {
            return -1;
        }
        if (str[j + 1] == 'w'){
            res += 1 << (W_OFF - j);
        } else if (str[j + 1] != '-') {
            return -1;
        }
        if (str[j + 2] == 'x') {
            res += 1 << (X_OFF - j);
        } else if (str[j + 2] != '-') {
            return -1;
        }
    }
    return res;
}

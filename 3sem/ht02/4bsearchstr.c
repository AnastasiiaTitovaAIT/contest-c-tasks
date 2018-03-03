#include<stdio.h>
#include<string.h>
int
bsearchstr(const unsigned char * const *arr, int size, const unsigned char *key)
{
    int first = 0;
    int last = size;
    int mid;
    int s;
    if (size == 0) {
        return -1;
    }
    while (first < last) {
        mid  = first + (last - first) / 2;
        s = strcmp(key, arr[mid]);
        if (!s) {
            return mid;
        }
        if (s < 0) {
            last = mid;
        } else if (s > 0) {
            first = mid + 1;
        }
    }
    return -1;
}

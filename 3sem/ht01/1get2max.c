#include<stdio.h>
int
getmax2(int count, const int *arr)
{
    int max = arr[0];
    int max2 = arr[1];
    for (int i = 1; i < count; i++) {
        if (arr[i] > max) {
            max2 = max;
            max = arr[i];
        } else if (arr[i] > max2) {
            max2 = arr[i];
        }
    }
    return max2;
}

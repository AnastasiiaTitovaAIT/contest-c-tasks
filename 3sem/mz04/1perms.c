#include<stdio.h>
int
main(int argc, const char **argv)
{
    int dig, m;
    unsigned int roll;
    int i;
    for(i = 1; i < argc; i++) {
        sscanf(argv[i], "%o", &dig);
        m = 2;
        roll = 0700;
        while(m >= 0) {
            switch((dig & roll) >> m * 3) {
            case 0:
                printf("%s", "---");
                break;
            case 1:
                printf("%s", "--x");
                break;
            case 2:
                printf("%s", "-w-");
                break;
            case 3:
                printf("%s", "-wx");
                break;
            case 4:
                printf("%s", "r--");
                break;
            case 5:
                printf("%s", "r-x");
                break;
            case 6:
                printf("%s", "rw-");
                break;
            case 7:
                printf("%s", "rwx");
                break;
            default :
                break;
            }
        roll >>= 3;
        m--;
        }
        printf("\n");
    }
}

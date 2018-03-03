#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int
main(int argc, char **argv)
{
    int st;
    for (int i = 1; i < argc; i++) {
        switch(fork())
        {
        case 0:
            execlp(argv[i], argv[i], NULL);
            exit(1);
        default:
            wait(&st);
            if((WIFEXITED(st) && WEXITSTATUS(st)) || WIFSIGNALED(st)) {//неуспешное завершение
                exit(1);
            }
        }

    }
    return 0;
}

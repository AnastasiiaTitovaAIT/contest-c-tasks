#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

enum{ MAX_STR = 1000};

typedef struct shmem{
    int pid;
    int count;
    char str[MAX_STR];
} shmem;

int fl1 = 0, fl2 = 0;

void
changef1(int sig)
{
    signal(SIGUSR2, changef1);
    fl1 = 1;
}

void
changef2(int sig)
{
    signal(SIGUSR1, changef2);
    fl2 = 1;
}

int
main(int argc, char **argv)
{
    int key;
    sscanf(argv[1], "%d", &key);
    shmem *shmaddr;
    int shmid = shmget(key, sizeof(*shmaddr), IPC_CREAT | 0666);
    shmaddr = shmat(shmid, NULL, 0);
    shmaddr->count = 0;
    int pid1, pid2;
    if(!(pid1 = fork())){
        signal(SIGUSR2, changef1);
        FILE *f = fopen(argv[2], "r");
        while(!fl1){
            usleep(1000);
        }
        pid2 = shmaddr->pid;
        fl1 = 0;
        while(fgets(shmaddr->str, MAX_STR, f) != NULL){
            (shmaddr->count)++;
            kill(pid2, SIGUSR1);
            while(!fl1){
            usleep(1000);
            }
            fl1 = 0;
        }
        kill(pid2, SIGKILL);
        fclose(f);
        return 0;
    }
    if(!fork()){
        signal(SIGUSR1, changef2);
        shmaddr->pid = getpid();
        kill(pid1, SIGUSR2);
        int i;
        fl2 = 0;
        while(1){
            while(!fl2){
                usleep(1000);
            }
            for(i = strlen(shmaddr->str) - 1; i >= 0 && isspace(shmaddr->str[i]); i--);
            i++;
            if(shmaddr->str[0] == '\n'){
                printf("0\n");
                fflush(stdout);
            } else {
                printf("%d\n", i);
                fflush(stdout);
            }
            fl2 = 0;
            kill(pid1, SIGUSR2);
        }
    }
    wait(NULL);
    wait(NULL);
    printf("%d\n", shmaddr->count);
    fflush(stdout);
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}

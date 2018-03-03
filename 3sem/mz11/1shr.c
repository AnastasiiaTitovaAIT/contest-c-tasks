#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int fl1, fl2;
int amount;
int chp[2];
void sf (int s);
enum { BUFSIZE = 1000 };
int main(int argc, char **argv)
{
    int target, key, count;
    sscanf(argv[1], "%d", &key);
    int shmid = shmget(key, BUFSIZE + sizeof(count), IPC_CREAT | 0666);
    char *shar = shmat(shmid, NULL, 0);
    if(!(chp[0] = fork())) {
        signal(SIGUSR1, sf);
        FILE *fp = fopen(argv[2], "r");
        if(!fp) {
            printf("0\n");
            fclose(fp);
            exit(0);
        }
        while(!fl1) {
            usleep(10000);
        }
        sscanf(shar, "%d", &target);
        fl1 = 0;
        while(fgets(shar, BUFSIZE, fp) > 0) {
            kill(target, SIGUSR2);
            while(!fl1) {
                usleep(10000);
            }
            fl1 = 0;
        }
        kill(target, SIGTERM);
        fclose(fp);
        exit(0);
    }
    if (!fork()) {
        signal(SIGUSR2, sf);
        chp[1] = getpid();
        target = chp[0];
        sprintf(shar, "%d", chp[1]);
        kill(target, SIGUSR1);
        while(1) {
            while(!fl2) {
                usleep(10000);
            }
            fl2 = 0;
            int i;
            for(i = strlen(shar) - 1; i >= 0; i--) {
                if(!isspace(shar[i])) {
                    break;
                }
            }
            if(shar[0] == '\n'){
                printf("0\n");
                fflush(stdout);
            } else {
                printf("%d\n", i + 1);
                fflush(stdout);
            }
            amount += 1;
            sprintf(shar + BUFSIZE, "%d", amount);
            kill(target, SIGUSR1);
        }
    }
    wait(NULL);
    wait(NULL);
    sscanf(shar + BUFSIZE, "%d", &count);
    printf("%d\n", count);
    fflush(stdout);
    shmdt(shar);
    shmctl(shmid, IPC_RMID, (int) 0);
    return 0;
}

void sf(int sig)
{
    if (sig == SIGUSR1) {
        signal(SIGUSR1, sf);
        fl1 = 1;
        return ;
    } else {
        signal(SIGUSR2, sf);
        fl2 = 1;
    }
}

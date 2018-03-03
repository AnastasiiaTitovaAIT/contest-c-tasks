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

void f(int s);
void f2(int s);
volatile int cnt, fl;
FILE *fp;
int chp[2];
char *shar;
enum { BUFSIZE = 1000 };
int
main(int argc, char **argv)
{
    int key, st;
    sscanf(argv[1], "%d", &key);
    int shmid = shmget(key, BUFSIZE, IPC_CREAT | 0666);
    shar = shmat(shmid, 0, 0);
    if (!fork()) {
        signal(SIGUSR1, f);
        while(!chp[1]) {
            sscanf(shar, "%d", &chp[1]);
        }
        printf("here\n");
        chp[0] = getpid();
        kill(chp[1], SIGUSR2);
        while(1);
    } else {
        if(!fork()) {
            signal(SIGUSR2, f2);
            int p = getpid();
            sprintf(shar, "%d\n", p);
           /* while(!fl) {
                usleep(1000);
            }*/
            fp = fopen(argv[2], "r");
            while(1);
        } else {
            wait(&st);
            wait(&st);
            printf("%d\n", cnt);
            fflush(stdout);
            shmdt(shar);
            shmctl(shmid, IPC_RMID, (int) 0);
            return 0;
        }
    }
}

void f (int sig)
{
    signal(SIGUSR1, f);
    char *buf = malloc(BUFSIZE);
    memcpy(buf, shar, strlen(shar));
    memset(shar, 0, strlen(shar));
    int i;
    for(i = strlen(buf) - 1; i >= 0; i--) {
        if(!isblank(buf[i])) {
            break;
        }
    }
    puts(buf);
    cnt++;
    printf("%d\n", i + 1);
    fflush(stdout);
    free(buf);
    kill(chp[1], SIGUSR2);
}

void f2(int sig)
{
    signal(SIGUSR2, f2);
  /*  static int c = 0;
    if(!c){
        c++;
        fl = 1;
        return;
    }*/
    char *buf = malloc(BUFSIZE);
    if (fgets(buf, BUFSIZE, fp) > 0) {
        memcpy(shar, buf, strlen(buf));
        memset(buf, 0, BUFSIZE);
    } else {
        fclose(fp);
        free(buf);
        kill(chp[0], SIGTERM);
        raise(SIGTERM);
    }
    free(buf);
    kill(chp[0], SIGUSR1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHARE_FILE      "./share_file.txt"
#define BUFFER_SIZE     1024

struct share_mm {
    int pid_r;
    int pid_w;
    char buffer[BUFFER_SIZE];
}*shmaddr;

void write_handler(int signum);

int main(int argc, char *argv[])
{
    int shmid;
    key_t key;

    key = ftok(SHARE_FILE, 0);
    if((shmid = shmget(key, sizeof(struct share_mm), 0666|IPC_CREAT)) == -1) {
        printf("shmget error!!!\n");
        exit(1);
    } else {
        printf("shmid is %d\n",shmid);
        //system("ipcs -m");
    }

    if((shmaddr = shmat(shmid, 0, 0)) == (void *)-1) {
        printf("shmat error!!!\n");
        exit(1);
    } else {
        printf("shmaddr is %p\n", shmaddr);
        //system("ipcs -m");
    }

    shmaddr->pid_w = getpid();
    signal(SIGUSR2, write_handler);
    memset((void *)shmaddr->buffer, 0, BUFFER_SIZE);
    printf("Please write message:");
    //gets(shmaddr->buffer);
    fgets(shmaddr->buffer, sizeof(shmaddr->buffer), stdin);
    do{
        kill(shmaddr->pid_r, SIGUSR1);
        pause();
    }while(strncmp(shmaddr->buffer, "quit", 4));

    if(shmdt(shmaddr) < 0) {
        printf("shmdt error!!!\n");
        exit(1);
    }

    if((shmctl(shmid, IPC_RMID, NULL)) < 0) {
        printf("shmctl error!!!\n");
        exit(1);
    }

    exit(0);
    return 0;
}

void write_handler(int signum)
{
    memset((void *)shmaddr->buffer, 0, BUFFER_SIZE);
    printf("Please write message:");
    //gets(shmaddr->buffer);
    fgets(shmaddr->buffer, sizeof(shmaddr->buffer), stdin);
}
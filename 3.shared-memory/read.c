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

void read_handler(int signum);

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

    shmaddr->pid_r = getpid();
    shmaddr->pid_w = 0;
    memset((void *)shmaddr->buffer, 0, BUFFER_SIZE);

    while(shmaddr->pid_w == 0);

    signal(SIGUSR1, read_handler);
    do{
        pause();
        kill(shmaddr->pid_w, SIGUSR2);
    }while(strncmp(shmaddr->buffer, "quit", 4));
    
    if(shmdt(shmaddr) < 0) {
        printf("shmdt error!!!\n");
        exit(1);
    }

    exit(0);
    return 0;
}

void read_handler(int signum)
{
    printf("read message:%s", shmaddr->buffer);
}
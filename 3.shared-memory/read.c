#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHARE_FILE      "./share_file.txt"
#define BUFFER_SIZE     1024

struct share_mm {
    int pid_r;
    int pid_w;
    char buffer[BUFFER_SIZE];
};

int main(int argc, char *argv[])
{
    int shmid;
    key_t key;

    key = ftok(SHARE_FILE, 0);
    shmid = shmget()

    return 0;
}
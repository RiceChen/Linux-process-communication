#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include "sensor_data.h"

void write_mem_handler(int signum)
{
    //通过随机数种子，模拟传感器采集数据
    srand((int)time(NULL));
    shm_addr->temperaturn = (float)(rand() % 100);
    shm_addr->humidness = (float)(rand() % 100);
    shm_addr->illumination = (float)(rand() % 100);
}

int main(int argc, char *argv[])
{
    int shm_id;
    key_t key;
    
    //创建key
    key = ftok(SHARE_MEM_FILE, 0);

    //创建共享内存
    if((shm_id = shmget(key, sizeof(struct share_mem), 0666|IPC_CREAT)) == -1) {
        printf("shmget error!!!\n");
        exit(1);
    } else {
        printf("shmid is %d\n",shm_id);
    }

    //内存映射，并获取映射地址
    if((shm_addr = shmat(shm_id, 0, 0)) == (void *)-1) {
        printf("shmat error!!!\n");
        exit(1);
    } else {
        printf("shmaddr is %p\n", shm_addr);
    }
    
    //通过信号实现进程的异步通信
    shm_addr->pid_w = getpid();
    signal(SIGUSR2, write_mem_handler);

    shm_addr->kill_flag = 0;

    //通过随机数种子，模拟传感器采集数据
    srand((int)time(NULL));
    shm_addr->temperaturn = (float)(rand() % 100);
    shm_addr->humidness = (float)(rand() % 100);
    shm_addr->illumination = (float)(rand() % 100);

    //printf("%f\t%f\t%f\n",shm_addr->temperaturn,shm_addr->humidness,shm_addr->illumination);

    //向读进程发送信号
    do {
        kill(shm_addr->pid_r, SIGUSR1);
        pause();
    } while(shm_addr->kill_flag == 1);

    //断开共享内存连接
    if(shmdt(shm_addr) < 0) {
        printf("shmdt error!!!\n");
        exit(1);
    }

    //删除共享内存对象
    if((shmctl(shm_id, IPC_RMID, NULL)) < 0) {
        printf("shmctl error!!!\n");
        exit(1);
    }

    exit(0);
    return 0;
}
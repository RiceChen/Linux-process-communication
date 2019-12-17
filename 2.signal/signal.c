#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void alarm_handler(int signum);

int main(int argc, int *argv[])
{
    int ret;
    signal(SIGALRM, alarm_handler);

    ret = alarm(3);
    pause();
    printf("The alarm return value is (%d)!!!\n", ret);
    
    return 0;
}

void alarm_handler(int signum)
{
    printf("alarm:(%d)!!!\n", signum);
}
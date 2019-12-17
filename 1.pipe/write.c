#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>

#define PIPE_FILE       "./pipe_file"
#define BUFFER_SIZE     PIPE_BUF        //It`s defined in limits.h

#define SEND_DATA       "Linux-process-communication"

int main(int argc, char *argv[])
{
    int pipe_fd;
    char buffer[BUFFER_SIZE];

    if(access(PIPE_FILE, F_OK) == -1) {
        if(mkfifo(PIPE_FILE, 0666) < 0) {
            perror("mkfifo error!!!\n");
            return -1;
        }
    }
    printf("mkfifo success!!\n");

    if((pipe_fd = open(PIPE_FILE, O_WRONLY)) == -1) {
        perror("open PIPE_FILE fail!!!\n");
        return -1;
    }
    printf("open success!!\n");

    strcpy(buffer, SEND_DATA);
    if(write(pipe_fd, buffer, strlen(buffer)) > 0 ) {
        printf("write PIPE_FILE: %s\n",buffer);
    }

    close(pipe_fd);
    return 0;
}
     
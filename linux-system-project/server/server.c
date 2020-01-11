#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#define PORT                2020    //端口号
#define MAX_QUE_CONN_NU     20      //请求队列中允许的最大请求书

static void *r_client_data_pthread(void *arg)
{
    //while(1) {
        printf("chenjiafan");
    //}
}

int main(int argc, char *argv[])
{
    int server_fd,client_fd;
    struct sockaddr_in server_sockaddr, client_sockaddr;
    int sin_size;
    pid_t r_serial_pid, client_pid;
    pthread_t r_client_data;
    char buf[2048];
    int length;

    //创建socket
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket: create fail!!!\n");
        exit(1);
    }

    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_sockaddr.sin_zero), 8);

    int i = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int));

    //指定ip地址，端口号
    if(bind(server_fd, (struct sockaddr *)&server_sockaddr, sizeof(struct sockaddr)) == -1) {
        perror("socket: bind fail!!!\n");
        exit(1);
    }
    //监听外来请求状态
    if(listen(server_fd, MAX_QUE_CONN_NU) == -1) {
        perror("socket: listen fail!!!\n");
        exit(1);
    }

    

    while(1) {
        sin_size = sizeof(struct sockaddr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_sockaddr, &sin_size);
        client_pid = fork();

        if(client_pid == 0) {
            close(server_fd);
            if(pthread_create(&r_client_data, NULL, r_client_data_pthread, (void *)(1)) == -1) {
                perror("create pthread: read client data fail!!!\n");
                exit(1);
            }

        }
        else if (client_pid > 0){
            close(client_fd);
        }
    }

    r_serial_pid = fork();
    if(r_serial_pid == 0) {
        if(pthread_create(&r_client_data, NULL, r_client_data_pthread, (void *)(1)) == -1) {
            perror("create pthread: read client data fail!!!\n");
            exit(1);
        }

        //while(1) {
            printf("dsad");
        //}
    }
*/
    close(server_fd);

    return 0;
}
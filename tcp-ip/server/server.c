#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT                1234
#define MAX_QUE_CONN_NM     10
#define BUFFER_SIZE         1024

int main(int argc, char *argv[])
{
    struct sockaddr_in server_sockaddr, client_sockaddr; 
    int sock_fd;
    int client_fd;
    int sin_size;
    int recv_byte;
    char buf[BUFFER_SIZE];

    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
        perror("create socket fail!!!\n");
        exit(1);
    }
    printf("create socket success!!!\n");

    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_sockaddr.sin_zero), 8);

    int i = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int));

    if(bind(sock_fd, (struct sockaddr *)& server_sockaddr, sizeof(struct sockaddr)) == -1) {
        perror("bind fail!!!\n");
        exit(1);
    }

    if(listen(sock_fd, MAX_QUE_CONN_NM) == -1) {
        perror("listen fail!!!\n");
        exit(1);
    }

    sin_size = sizeof(struct sockaddr);
    if((client_fd = accept(sock_fd, (struct sockaddr *)& client_sockaddr, &sin_size)) == -1) {
        perror("accept fail!!!\n");
        exit(1);
    }

    memset(buf, 0, sizeof(buf));
    if((recv_byte = recv(client_fd, buf, BUFFER_SIZE, 0)) == -1) {
        perror("received fail!!!\n");
        exit(1);
    }

    printf("received a message: %s\n", buf);

    close(sock_fd);
    
    return 0;
}
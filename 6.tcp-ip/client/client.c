#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>


#define PORT                1234
#define MAX_QUE_CONN_NM     10
#define BUFFER_SIZE         1024

int main(int argc, char *argv[])
{
    struct sockaddr_in server_sockaddr;
    int sock_fd;
    struct hostent *host;
    int send_byte;
    char buf[BUFFER_SIZE];

    if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
        perror("create socket fail!!!\n");
        exit(1);
    }
    printf("create socket success!!!\n");

    if((host = gethostbyname("localhost")) == NULL) {
        perror("get host by name fail!!!\n");
        exit(1);
    }

    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_sockaddr.sin_zero), 8);

    if(connect(sock_fd, (struct sockaddr *)&server_sockaddr, sizeof(struct sockaddr)) == -1) {
        perror("connect fail!!!\n");
        exit(1);
    }

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", "Rice TCP/IP demo");

    if((send_byte = send(sock_fd, buf, sizeof(buf), 0) == -1)) {
        perror("send fail!!!\n");
        exit(1);
    }
    close(sock_fd);

    return 0;
}
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>
 
 
#define SERVER_PORT 2020
#define MAXLINE 4096
 
int main(void)
{
	struct sockaddr_in serveraddr;
	int confd,len;
	char ipstr[] = "10.13.3.12";//这是服务器的地址，使用ifconfig来查看
	char buf[MAXLINE];
	//1.创建一个socket
	confd = socket(AF_INET,SOCK_STREAM,0);
	//2.初始化服务器地址，指明我要连接哪个服务器
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET,ipstr,&serveraddr.sin_addr.s_addr);
	serveraddr.sin_port = htons(SERVER_PORT);
	//3.链接服务器
	connect(confd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	printf("asdsadasds");
    while(fgets(buf,sizeof(buf),stdin)){
	//4.请求服务器处理数据
	write(confd,buf,strlen(buf));
	}
	//5.关闭socket
	close(confd);
	return 0;
}
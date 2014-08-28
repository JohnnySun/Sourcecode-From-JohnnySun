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

#ifndef INFTIM     /*�������Ͻ��ͣ�POSIX�淶Ҫ��INFTIM��ͷ�ļ�<poll.h>�ж��壬����*/
#define INFTIM -1  /*���ϵͳ��Ȼ����������ͷ�ļ�<sys/stropts.h>�У����Ǿ����ҵĲ���*/
#endif             /*��ʹ�������������ļ���������Ҳ�Ҳ�������֪�ν⡣�����Լ������ˡ�*/

int main(int argc, char *argv[])
{
    int i, maxi, listenfd, connfd, sockfd;
    int nready;
    ssize_t n;
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr;
    struct hostent  *hp;
    char buf[BUFSIZ];
    struct pollfd client[OPEN_MAX]; /*����poll������һ������������*/
    if( argc != 2 )
    {
        printf("Please input %s <hostname>\n", argv[0]);
        exit(1);
    }

    //����socket
    if( (listenfd = socket(AF_INET, SOCK_STREAM,0)) < 0 )
    {
        printf("Create socket error!\n");
        exit(1);
    }

    //���÷�������ַ�ṹ
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
//�󶨵�ַ
    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 )
    {
        printf("IPaddress bound failure!\n");
        exit(1);
    }

    //��ʼ����
    listen(listenfd, LISTENQ);

    client[0].fd = listenfd;         /*�������еĵ�һ��Ԫ�����óɼ���������*/

    client[0].events = POLLIN;  /*�������������ó���ͨ�����ȼ������ݿɶ����˴�����ΪPOLLRDNORM��
                                      ������ôҲ���벻��ȥ �������������Ҳ��������Ծ���ʱ�ĳ���POLLIN���������
                                     ϣ���Ժ���Ū�����
                                    */

    for(i = 1;i < OPEN_MAX; ++i)     /*�����е�����Ԫ�ؽ���ʱ���óɲ�����*/
       client[i].fd = -1;
    maxi = 0;

    while(1)
    {
        nready = poll(client, maxi+1,INFTIM); //������������poll��
        if( client[0].revents & POLLIN/*POLLRDNORM*/ ) /*�Ȳ��Լ���������*/
        {
            connfd = accept(listenfd,(struct sockaddr*)&servaddr, &clilen);
            for(i = 1; i < OPEN_MAX; ++i)
                if( client[i].fd < 0 )
                {
                    client[i].fd = connfd;  /*�������Ӽ��뵽����������*/
                    client[i].events = POLLIN;//POLLRDNORM; /*����������ͨ���ݿɶ�*/
                    break;
                }
            if( i == OPEN_MAX )
            {
                printf("too many clients"); //���ӵĿͻ���̫���ˣ����ﵽ���ֵ��
                exit(1);
            }

            if( i > maxi )
                maxi = i;  //maxi��¼��������Ԫ�صĸ���

            if( --nready <= 0 )
                continue;   //���û�пɶ����������ˣ������¼�������
        }

        for(i = 1; i <= maxi; i++)  /*���Գ������������Ժ����������������*/
        {
            if( (sockfd = client[i].fd) < 0) /*�����ǰ�����ֲ����ã��Ͳ�����һ��*/
                continue;

            if(client[i].revents & (POLLIN/*POLLRDNORM*/ | POLLERR))/*�����ǰ�����ַ��ص�����ͨ���ݿɶ����������*/
            {
                if( (n = read(sockfd, buf, MAXLINE)) < 0) //���׽ӿ��ж�����
                {
                    if( errno == ECONNRESET) //������ӶϿ����͹ر����ӣ����赱ǰ������������
                    {
                        close(sockfd);
                        client[i].fd = -1;
                    }
                    else
                        perror("read error");
                }
                else if(n == 0) //������ݶ�ȡ��ϣ��ر����ӣ����õ�ǰ������������
                {
                    close(sockfd);
                    client[i].fd = -1;
                }
                else
                    write(sockfd, buf, n); //��ӡ����

                if(--nready <= 0)
                    break;

            }
        }
    }

    exit(0);
}
#include <stdio.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "netdb.h"
int main() {
//    unlink("server_socket");
    int listenfd, connfd; //文件描述符
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;// ip port 文件
    char buff[105];
    int portt=9003;
    int res,nbytes;
    time_t ticks;
    struct hostent *hp= gethostbyname("mzunitst.top");

    listenfd = socket(AF_INET, SOCK_STREAM, 0);//SOCK_STREAM为字节流套接字
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;//IVP4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);// 0.0.0.0 接受所有IP的请求 network long 32b IP
    servaddr.sin_port = htons(portt);//服务器端口 short 16b端口
    printf("start...\t");

    res=bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(res<0){
        perror("bind");
        return 0;
    }
    res=listen(listenfd, 5);
    if(res<0){
        perror("listen");
        return 0;
    }
    printf("finish\n");


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while(1) {

        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
        if(connfd<0){
            perror("accept");
            return 0;
        }
        inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff));//将二进制IP转换为点分十进制的字符串IP
        printf("connection from %s, port %d\n", buff, ntohs(cliaddr.sin_port));// ntos :net to short ,将 net的port 转为短整型

        nbytes=0;
        char s[101];
        if (nbytes<3){
            nbytes += read(connfd, s, sizeof (s)); //字符串 strlen sizeof read的参数
            printf("strlen: %d,s: %s\n", strlen(s),s);
            printf("readd %d bytes content from client: %s\n", nbytes, s);
        }

        for(int i=0;i<nbytes;i++){
            if(s[i]>='a' && s[i]<='z')
            s[i]=s[i]-32;
        }
        write(connfd,s, nbytes);
        close(connfd);
        printf("closed\n\n");
    }
#pragma clang diagnostic pop
}




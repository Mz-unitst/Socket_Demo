#include <stdio.h>
#include <netinet/in.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

void checkResult (int ResCode, char* methods );

int main() {
    printf("Hello, Linuxxx!\n");
    checkResult(-1, "test");
    int listenfd, connfd; //句柄
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;
    char buff[10086];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9001);

    checkResult(bind(listenfd, &servaddr, sizeof(servaddr)), "bind");
    checkResult(listen(listenfd, 10), "listen");//10个队列?
    printf("bind && listen success!\n");

    for (;;) {
        len = sizeof(cliaddr);
        checkResult(connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len),"accept");
        inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff));
        printf("connection from %s, port %d\n", buff, ntohs(cliaddr.sin_port));
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        printf("buff:%s\n",buff);
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
}

void checkResult (int ResCode, char* methods ){
    if(ResCode<0){
        printf("%s ERROR\n",methods);
    }
}


#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define DEFAULT_PORT 8000
#define MAXLIN 4096
 
int main(int argc,char **argv)
{
    int socket_fd,connect_fd;
    struct sockaddr_in servaddr;
    char buff[4096];
    int n;
    int len;

    // Initialization
    if((socket_fd=socket(AF_INET,SOCK_STREAM,0)) == -1) // AF_INET is ipv4, AF_INET6 is ipv6
    {
        printf("create socket error:%s(errno :%d)\n",strerror(errno),errno);
        exit(0);
    }
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    // set IP address to INADDR_ANY, let system get it automatically
    servaddr.sin_port=htons(DEFAULT_PORT);
    // set the port to DEFAULT_PORT (8000)

    // bind local address to the built socket
    if(bind(socket_fd,(struct sockaddr*)&servaddr,sizeof(servaddr)) == -1)
    {
        printf("bind socket error:%s(errno:%d)\n",strerror(errno),errno);
        exit(0);
    }

    // start to listen to client connect, the second parameter is the max number of listen
    if(listen(socket_fd,10) == -1)
    {
        printf("listen socket error:%s(errno:%d)\n",strerror(errno),errno);
        exit(0);
        
    }
    printf("======waiting for client's request=====\n");
    while(1){
        if((connect_fd = accept(socket_fd,(struct sockaddr*)NULL,NULL)) == -1){
            printf("accept socket error :%s(errno:%d)\n",strerror(errno),errno);
            exit(1);
        }
        printf("new client connect.\n");
        if(!fork()){
            FILE *fpRead = fopen("mydata.txt", "r");
            if (fpRead == NULL){
                perror("Read file error");
                return 0;
            }
            printf("file open ends, start to send.\n");
            while (fgets(buff, MAXLIN, fpRead) != NULL){
                len = strlen(buff);
                if (send(connect_fd, buff, len, 0) == -1){
                    perror("send error");
                    close(connect_fd);
                    exit(0);
                }
            }
            printf("file sending ends.\n");
            printf("\n");
            fclose(fpRead);
        }
        close(connect_fd);
    }
    
    close(socket_fd);
    printf("server socket closed.\n");
    return 0;
}

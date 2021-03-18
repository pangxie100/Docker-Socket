#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <netdb.h>
#define MAXLIN 4096
 
int main(int argc,char **argv)
{
    int sockfd,rec_len;
    char sendline[4096];
    char buff[MAXLIN];
    struct sockaddr_in servaddr;

    const char * inetAddr;
    struct hostent *he;
    
    he = gethostbyname("server_container_and_dns_name");

    // now it doesn't need other argument, just ./client
    /*
    if(argc!=2)
    {
        printf("usage:./client <ipaddress>\n");
        exit(0);
    }
    */
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) // AF_INET is ipv4, AF_INET6 is ipv6
    {
        printf("create socket error:%s(error:%d)\n", strerror(errno),errno);
        exit(0);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);

    inetAddr = inet_ntoa(*(struct in_addr*)he->h_addr);

    if(inet_pton(AF_INET, inetAddr, &servaddr.sin_addr) <= 0)
    {
        printf("inet_pton error for %s\n", inetAddr);
        exit(0);
    }
    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error:%s(errno:%d)\n", strerror(errno), errno);
        exit(0);
    }
    FILE *fpWrite = fopen("../client_storage/mydata_client_copy.txt", "w");
    printf("client receive file:(between ==== and ====)\n");
    printf("====\n");
    bzero(buff, sizeof(buff));
    while ((rec_len = recv(sockfd,buff,MAXLIN,0)) > 0){
        printf("%s", buff);
        fwrite(buff, sizeof(char), rec_len, fpWrite);
        bzero(buff, sizeof(buff));
    }
    printf("\n====\n");
    fclose(fpWrite);
    close(sockfd);
    return 0;
}

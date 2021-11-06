#include "stdio.h"
#include "anet.h"
#include "zmalloc.h"
#include <sys/socket.h>
#include <unistd.h>
#include "sys/socket.h"
#define NET_IP_STR_LEN 46 /* INET6_ADDRSTRLEN is 46, but we need to be sure */


int main() {
    // 错误信息
    char *neterr = zmalloc(10);

    printf("staring...\n");

    // 端口6380
    int serverSocket = anetTcpServer(neterr, 6380,"*" , 2);
    if ( ! neterr ) {
        printf("start err %s \n", neterr);
        return 1;
    }
    printf("listening...%d \n",serverSocket );

    while(1){
        int cfd;
        // 错误信息
        char* err = zmalloc(20);
        char cip[NET_IP_STR_LEN];
        int cport;
        cfd = anetTcpAccept(err, serverSocket, cip, sizeof(cip), &cport);
        if ( cfd == ANET_ERR )
            continue;
        printf("accept...%d\n",cfd);
        char buf[1024];
        recv(cfd, buf, sizeof(buf), MSG_WAITALL);
        printf("recv from %s:%d  %s\n",cip, cport, buf);
        close(cfd);
    }
    close(serverSocket);
}

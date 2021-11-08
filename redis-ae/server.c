#include "anet.h"
#include "zmalloc.h"
#include <sys/socket.h>
#include <unistd.h>
#include "sys/socket.h"
#define NET_IP_STR_LEN 46 /* INET6_ADDRSTRLEN is 46, but we need to be sure */
#include "ae.h"

void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask);

#define MAX_ACCEPTS_PER_CALL 1000
#define UNUSED(V) ((void) V)


void acceptTcpHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    int cport, cfd, max = MAX_ACCEPTS_PER_CALL;
    char cip[NET_IP_STR_LEN];
    UNUSED(el);
    UNUSED(mask);
    UNUSED(privdata);

    while(max--) {
        char* neterr;
        neterr = zmalloc(100);
        cfd = anetTcpAccept(neterr, fd, cip, sizeof(cip), &cport);
        if (cfd == ANET_ERR) {
            continue;
        }
        anetCloexec(cfd);

        printf("accept...%d\n",cfd);
        char buf[1024];
        recv(cfd, buf, sizeof(buf), MSG_WAITALL);
        printf("recv from %s:%d  %s\n",cip, cport, buf);
        close(cfd);

    }
}



int main() {
    // 错误信息
    char *neterr = zmalloc(10);

    printf("staring...\n");
    aeEventLoop *el;
    el = aeCreateEventLoop(100);



    // 端口6380
    int serverSocket = anetTcpServer(neterr, 6380,"*" , 2);
    if ( ! neterr ) {
        printf("start err %s \n", neterr);
        return 1;
    }
    printf("listening...%d \n",serverSocket );

    if (aeCreateFileEvent(el, serverSocket, AE_READABLE, acceptTcpHandler,NULL) == AE_ERR) {
        aeDeleteFileEvent(el, serverSocket, AE_READABLE);
        return 1;
    }

    aeMain(el);
    aeDeleteEventLoop(el);
    return 0;
 }

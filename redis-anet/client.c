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
    int port;
    port = 6380;
    char* addr;
    addr = "127.0.0.1";
    int fd = anetTcpNonBlockConnect(NULL,addr,port);
    char * hello = "hello";
    printf("send %s\n", hello);
    send(fd, hello, sizeof(hello),MSG_DONTWAIT );
    close(fd);
}

/*
 *  如何确定一个唯一的网络通信
 *  1. 源ip
 *  2. 目的ip
 *  3. 源端口号
 *  4. 目的端口号
 *  5. 协议
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void Usage(char *proc)
{
    printf("usage: %s [ip] [port]\n", proc);
}

// ip: server ip
// port: server port
int main(int argc, char *argv[])
{
    if(argc != 3){
        Usage(argv[0]);
        return 1;
    }

    // IPv4   UDP
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        perror("socket");       
        return 1;
    }

    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    int ret = connect(fd, (struct sockaddr*)&addr, len);
    if(ret < 0){
        perror("connect");
        return 2;
    }
 
    while(1){
        char buf[1024] = {0};
        printf(">: ");
        fflush(stdout);
        ssize_t read_size = read(0, buf, sizeof(buf)-1);
        if(read_size < 0){
            perror("read");
            continue;
        }
        if(read_size == 0){
            printf("godabye\n");
            return 3;
        }
        buf[read_size] = '\0';

        write(fd, buf, strlen(buf));

        char buf2[1024] = {0};
        read_size = read(fd, buf2, sizeof(buf2));
        if(read_size < 0){
            perror("read");
            continue;
        }
        if(read_size == 0){
            printf("godabye\n");
            return 3;
        }
        printf("server: %s\n", buf2);
    }

    //echo服务器

    return 0;
}


/*
 * 一个服务器典型逻辑
 *  1. 初始化，指定ip地址和端口号，加载所需要的数据文件
 *  2. 进入事件循环
 *      a. 读取客户端数据
 *      b. 数据计算
 *      c. 响应客户端
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
    printf("%s [ip] [port]\n", proc);
}

int main(int argc, char *argv[])
{
    if(argc != 3){
        Usage(argv[0]);
        return 1;
    }

    // IPv4   TCP
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        perror("socket");       
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);//ip_addr
    addr.sin_port = htons(atoi(argv[2]));//port
    ;
    if(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        perror("bind");
        return 2;
    }

    int ret = listen(fd, 10);
    if(ret < 0){
        perror("listen");
        return 3;
    }

    while(1){
        struct sockaddr_in peer_addr;
        socklen_t len = sizeof(peer_addr);
        int new_fd = accept(fd, (struct sockaddr*)&peer_addr, &len);
        if(new_fd <0){
            perror("accept");
            continue;
        }

        while(1){
            char buf[1024] = {0};
            ssize_t read_size = read(new_fd, buf, sizeof(buf)-1);
            if(read_size < 0){
                perror("read");
                close(new_fd);
                return 5;
            }

            if(read_size == 0){
                printf("client close!");
                close(new_fd);
                break;
            }

            buf[read_size] = '\0';
            printf("[%s : %d]> %s\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port), buf);
            write(new_fd, buf, strlen(buf));
        }
    }

//    close(fd);
    return 0;
}


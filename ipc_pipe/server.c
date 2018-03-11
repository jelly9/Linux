#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main()
{   
    if(mkfifo("./mypipe", 0666 | S_IFIFO) < 0)//创建命名管道，默认权限是0666 
    { 
        perror("mkfifo"); 
        return 1; 
    } 

    int fd = open("mypipe", O_RDONLY);
    if(fd < 0){
        perror("open");
        return 1;
    }

    printf("open OK!\n");
    while(1){
        char buf[1024] = {0};
        ssize_t read_size = read(fd, buf, sizeof(buf)-1);
        if(read_size > 0){
            write(0, buf, strlen(buf));
        }else{
            printf("client quit!\n");
            return 0;
        }

    }

    return 0;
}

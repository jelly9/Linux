#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main()
{   

    int fd = open("mypipe", O_WRONLY);
    if(fd < 0){
        perror("open");
        return 1;
    }

    printf("open OK!\n");
    while(1){
        char buf[1024] = {0};
        ssize_t read_size = read(0, buf, sizeof(buf)-1);
        if(read_size < 0){
            perror("raed");
            return 1;
        }
        if(read_size == 0){
            sleep(1);
            continue;
        }

        write(fd, buf, strlen(buf));
    }

    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        return 1;
    }
    else if(pid > 0){//father
        printf("father start!\n");
        int status; 
        int ret = waitpid(-1, &status, WNOHANG);
        if(ret > 0 && (status & 0xff) == 0){
            printf("ret: %d\n", ret);
            printf("exit code: %d\n", (status>>8)&0xff);
        }else if (ret == 0){
            printf("no child finish\n");
        }
        else{
            printf("ret: %d\n", ret);
            printf("sig code: %d\n", status&0x7f);
        }
        printf("father end\n");
    }else{//child
        printf("child start!\n");
        sleep(100);
        printf("child end\n");
        exit(99);
    }

    return 0;
}

#include <stdio.h>
#include <memory.h>
#include <unistd.h>

int main()
{
    int _pipe[2];
    int ret = pipe(_pipe);// 创建管道
    if (-1 == ret){//如果创建失败则
        perror("pipe");
        return 1;
    }

    pid_t id = fork();
    if (id < 0){
        perror("fork");
        return 2;
    }
    else if(0 == id){
        close(_pipe[0]);//关闭读端，只往管道里写内容
        int i = 100;
        char *_mesg = NULL;
        while(i){
            _mesg = "i am a child!";
            write(_pipe[1], _mesg, strlen(_mesg)+1);
            sleep(1);
            i--;
        }
    }
    else{//父进程
        close(_pipe[1]);//关闭写端，只从管道里读取内容
        int i = 100;
        char _mesg[1024];
        while(i)
        {
            memset(_mesg, '\0', sizeof(_mesg));
            read(_pipe[0], _mesg, sizeof(_mesg));
            printf("child say: %s\n", _mesg);
            i--;
        }
    }

    return 0;
}

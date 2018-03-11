#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("pid:%d\n", getpid());		//调用进程的进程id
    printf("ppid:%d\n", getppid());	//调用进程的父进程id
    printf("uid:%d\n", getuid());		//调用进程的实际用户的id
    printf("euid:%d\n", geteuid());	//调用进程的有效用户id
    printf("gid:%d\n", getgid());		//调用进程的实际组id
    printf("egid:%d\n", getegid());	//调用进程的有效组id
    return 0;
}


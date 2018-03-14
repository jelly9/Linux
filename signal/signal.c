#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


//void myHandler(int sig)
//{
//    printf("sig: %d\n", sig);
//}
    
//void print_pending(sigset_t *p)
//{
//    int i = 1;
//    for(; i <= 32; ++i){
//        if(sigismember(p, i))
//            putchar('1');
//        else
//            putchar('0');
//    }
//    putchar('\n');
//}
//
//
void myHandler(int sig)
{
    pid_t id;
    printf("sig: %d\n", sig);
    while((id = waitpid(-1, NULL, WNOHANG)) > 0){
        printf("wait success: %d\n", id);
    }

    printf("child quit: %d\n", getpid());
}

//unsigned int mysleep(int scon)
//{
//    struct sigaction s, oldHandler;
//    unsigned int ret;
//    s.sa_handler = myHandler;
//    sigemptyset(&s.sa_mask);
//    s.sa_flags = 0;
//    sigaction(SIGALRM, &s, &oldHandler);//注册信号处理函数
//
//    alarm(scon);
//    pause();
//    ret = alarm(0);
//
//    sigaction(SIGALRM, &oldHandler, NULL);//回复之前的信号处理函数
//    return ret;
//}

//unsigned int mysleep(unsigned int scon)
//{
//    int ret = 0;
//    struct sigaction newH, oldH;
//    sigset_t newMask, oldMask, susMask;
//
//    newH.sa_handler = myHandler;
//    sigemptyset(&newH.sa_mask);
//    newH.sa_flags = 0;
//    sigaction(SIGALRM, &newH, &oldH);
//    
//    sigemptyset(&newMask);
//    sigaddset(&newMask, SIGALRM);
//    sigprocmask(SIG_BLOCK, &newMask, &oldMask);// 屏蔽SIGALRM
//    
//    alarm(scon);//睡眠等待
//
//    susMask = oldMask;
//    sigdelset(&susMask, SIGALRM);
//
//    //将信号屏蔽字设置为susMask并调用pause
//    sigsuspend(&susMask);
//    //sigsuspend返回时再回复屏蔽字，即又屏蔽SIGALRM
//
//    ret = alarm(0);
//
//    //用户主动还原最开始的信号屏蔽字
//    sigaction(SIGALRM, &oldH, NULL);
//
//    sigprocmask(SIG_SETMASK, &oldMask, NULL);
//
//    return ret;
//}

int main()
{

//    alarm(10);
//    int ret;
//    sleep(6);
//    ret=alarm(1);
//    printf("%d\n",ret);
//    pause();
//
//    while(1){
//        mysleep(1);
//        printf("hello world\n");
//    }
//

//    sigset_t s,p;
//    sigemptyset(&s);
//    sigemptyset(&p);
//    sigaddset(&s, SIGINT); // ctrl C
//    sigprocmask(SIG_BLOCK, &s, NULL);
//
//    while(1){
//        sigpending(&p);
//        print_pending(&p);
//        sleep(1);
//    }



//    signal(SIGINT, myHandler);

//    struct sigaction newH, oldH;
//    newH.sa_handler = myHandler;
//    sigemptyset(&newH.sa_mask);
//    newH.sa_flags = 0;
//    sigaction(SIGINT, &newH, &oldH);
//    while(1){
//
//    }



//    alarm(1);
//    kill(getpid(), 9);
//    int i = 0;
//    for(;;i++){
//        printf("%d\n", i);
//    }
//

    struct sigaction newAct, oldAct;
    newAct.sa_handler = myHandler;
    sigemptyset(&newAct.sa_mask);
    newAct.sa_flags = 0;
    sigaction(SIGCHLD, &newAct, &oldAct);

    int id = fork();
    if(id < 0){
        perror("fork");
        return -1;
    }else if(id == 0){//child
        printf("child start...\n");
        sleep(3);
        printf("child finish...\n");
        exit(0);
    }


    while(1){
        printf("father runing!\n");
        sleep(1);
    }

    sigaction(SIGCHLD, &oldAct, NULL);
    return 0;
}

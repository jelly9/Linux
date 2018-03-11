#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


// printf("pid : %d\n", getpid());
// printf("ret(child pid): %d\n", ret);
// printf("pid: %d\n",  getpid());
// printf("ppid: %d\n", getppid());
// printf("ret: %d\n", ret);

int g_val = 0;

int main()
{
    int i = 10;
    printf("g_val: %d, i: %d\n", g_val, i);

    pid_t ret = vfork();

    if(ret < 0){
        perror("fork");
        return 1;
    }
    else if(ret > 0){//father
        //sleep(3);
        printf("father start!\n");
        g_val++;
        i = 11;
        printf("g_val: %d, i: %d\n", g_val, i);
        printf("father end!\n");
        //wait(NULL);
    }else{//child
        printf("child start!\n");
        //g_val = 2;
        //i = 12;
        printf("g_val: %d, i: %d\n", g_val, i);
        printf("child end!\n");
        sleep(1);
 //       return 0;
    }

    printf("%d here\n", getpid());
   
   
//    int l_val = 20;
//    pid_t id = vfork();
//
//    if(id < 0){
//        perror("fork");
//        return 1;
//    }
//    else if(id > 0){//father
//        printf("father start: %d\n", getpid());
//        printf("main addr: %p\n", main);
//        printf("g_val in father: %p, %d\n", &g_val, g_val);
//        printf("l_val in father: %p, %d\n", &l_val, l_val);
//        printf("father end!\n");
//        //wait(NULL);
//    }else{//child
//        printf("child start: %d\n", getpid());
//        g_val = 100;
//        l_val = 200;
//        printf("main addr: %p\n", main);
//        printf("g_val in child: %p, %d\n", &g_val, g_val);
//        printf("l_val in child: %p, %d\n", &l_val, l_val);
//        printf("child end!\n");
//        //exit(0);
//        return 0;
//    }
//    
//    printf("father should run there: %d\n", getpid());
//    
    return 0;
}

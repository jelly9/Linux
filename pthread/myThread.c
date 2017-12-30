#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <pthread.h>


typedef struct Point{
    long x;
    long y;
}Point;

void *ThreadEntry(void *arg)
{
    (void *)arg;

    printf("thread start\n");
    sleep(3);
    printf("thread finish\n");

//    Point ret;
//    ret.x = 100;
//    ret.y = 200;
//    return (void*)&ret;

    Point *ret = (Point*)malloc(sizeof(Point));
    ret->x = 100;
    ret->y = 200;
    return (void*)ret;
//  pthread_exit(0);

//    while(1){
//        printf("I am a thread!\n");
//        sleep(1);
//    }
//    return NULL;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, ThreadEntry, NULL);
    if(ret != 0){
        printf("pthread create faild! %s/n", strerror(ret));
        return 1;
    }
    
    printf("befor join\n");


    void *thread_ret = NULL;
    
    pthread_join(tid, &thread_ret);
//    printf("retval: %p\n", thread_ret);
    Point *pt = (Point*)thread_ret;
    printf("retval x: %ld, y: %ld\n", pt->x, pt->y);

//    sleep(3);
//    pthread_cancel(tid);
//    printf("main thread tid: %lx\n", pthread_self());
//    printf("thread tid: %lx\n", tid);
    while(1){
        printf("main thread\n");
        sleep(1);
    }
    return 0;
}

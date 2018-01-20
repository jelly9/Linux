#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>


/* typedef struct Point{ */
/*     long x; */
/*     long y; */
/* }Point; */

/* void myHandler(int sig) */
/* { */
/*     printf("sig = %d\n", sig); */
/*     return; */
/* } */

/* void *ThreadEntry(void *arg) */
/* { */
/*     long long count = 0; */
/*     while(1){ */
/*         ++count; */
/*     } */
/* //    (void *)arg; */
/* // */
/* //    printf("thread start\n"); */
/* //    sleep(3); */
/* //    printf("thread finish\n"); */

/* //    Point ret; */
/* //    ret.x = 100; */
/* //    ret.y = 200; */
/* //    return (void*)&ret; */

/* //    Point *ret = (Point*)malloc(sizeof(Point)); */
/* //    ret->x = 100; */
/* //    ret->y = 200; */
/* //    return (void*)ret; */
/* //  pthread_exit(0); */


/*     while(1){ */
/*         printf("I am a thread!\n"); */
/*         sleep(1); */

/*         //int *ptr = NULL; */
/*         //*ptr = 100;//run there then send signal */
/*         //1. catch signal */
/*         //2. catch bad */
/*     } */
/*     return NULL; */
/* } */

//int64_t 64bit int 
int64_t TimeStamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000*1000 + tv.tv_usec;
}

typedef struct context{
    int *arr;
    size_t begin;
    size_t end;
}context;

void Calc(int *arr, size_t begin, size_t end)
{
    for(size_t i = begin; i < end; ++i){
        arr[i] = arr[i] * arr[i];
    }
}

void* ThreadEntry(void *arg)
{
    Calc(((context*)arg)->arr,((context*)arg)->begin, ((context*)arg)->end);
}

int main()
{
#if 0 
    const size_t size = 100000000;
    int *arr = (int*)malloc(size * sizeof(int));

    //int64_t begin = GetTickCount();
    int64_t begin = TimeStamp();
    Calc(arr, 0, size);
    int64_t end = TimeStamp();
    //int64_t end = GetTickCount();
    printf("time: %ld\n", end - begin);
#endif

    const size_t size = 100000000;
    int *arr = (int*)malloc(size * sizeof(int));
    while(1){
        int thread_size = 0;
        printf("input thread size: ");
        scanf("%d", &thread_size);
        if(thread_size <= 0){
            printf("quit\n");
            return 1;
        }

        pthread_t tid[thread_size];
        context ct[thread_size];
        size_t index_base = 0;

        int64_t begin = TimeStamp();
        for(size_t i = 0; i < thread_size; ++i){
            ct[i].arr = arr;
            ct[i].begin = index_base;
            ct[i].end = index_base + (size / thread_size);
            index_base += (size / thread_size);

            pthread_create(&tid[i], NULL, ThreadEntry, (void*)&ct);
        }
        for(size_t i = 0; i < thread_size; ++i){
            pthread_join(tid[i],NULL);
        }
        int64_t end  = TimeStamp();
        printf("time: %ld\n", end - begin);
    }
   /* //signal(SIGSEGV, myHandler); */
    /* pthread_t tid;//POSXI thread lib's id, option thread by this id; */
    /* int ret = pthread_create(&tid, NULL, ThreadEntry, NULL); */
/* //    pthread_detach(tid); */
    /* if(ret != 0){ */
    /*     printf("pthread create faild! %s/n", strerror(ret)); */
    /*     return 1; */
    /* } */
  
    /* long long count = 0; */
    /* while(1){ */
    /*     ++count; */
    /* } */
/* //    printf("befor join\n"); */


    /* void *thread_ret = NULL; */
    
/* //    pthread_join(tid, &thread_ret); */
/* //    printf("retval: %p\n", thread_ret); */
/* //    Point *pt = (Point*)thread_ret; */
/* //    printf("retval x: %ld, y: %ld\n", pt->x, pt->y); */

/* //    sleep(3); */
/* //    pthread_cancel(tid); */
/* //    printf("main thread tid: %lx\n", pthread_self()); */
/* //    printf("thread tid: %lx\n", tid); */
    /* while(1){ */
    /*     printf("main thread\n"); */
    /*     sleep(1); */
 //   }
    return 0;
}

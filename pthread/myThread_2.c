#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <pthread.h>

size_t g_count = 0;

void *ThreadEntry(void *arg)
{
    (void *)arg;

    while(1){
        usleep(1000*800);
        ++g_count;
    }
}
int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, ThreadEntry, NULL);
    pthread_detach(tid);
    if(ret != 0){
        printf("pthread create faild! %s/n", strerror(ret));
        return 1;
    }

    while(1){
        printf("%lu\n", g_count);
        sleep(1);
    }

    return 0;
}

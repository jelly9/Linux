#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

pthread_mutex_t lock;
size_t count = 0;

void ModifyCount()
{
    pthread_mutex_lock(&lock);
    printf("befor\n");
    ++count;
    sleep(3);
    printf("after\n");
    pthread_mutex_unlock(&lock);
}

void MyHandler()
{
    pthread_mutex_lock(&lock);
    //ModifyCount();
}

void* ThreadEntry(void *arg)
{
    for(size_t i = 0; i < 10000; ++i){
        ModifyCount();
    }
}

int main()
{
    signal(SIGINT, MyHandler);

    pthread_mutex_init(&lock, NULL);
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, ThreadEntry, NULL);
    pthread_create(&tid2, NULL, ThreadEntry, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("count: %ld\n", count);

    pthread_mutex_destroy(&lock);
    return 0;
}

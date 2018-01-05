#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock;

size_t count = 0;
void* ThreadEntry(void *arg)
{

    for(size_t i = 0; i < 50000000; ++i){
        //pthread_mutex_lock(&lock);
        ++count;
        //pthread_mutex_unlock(&lock);
    }
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, ThreadEntry, NULL);
    pthread_create(&tid2, NULL, ThreadEntry, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("count: %ld\n", count);
    return 0;
}

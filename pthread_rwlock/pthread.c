#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t g_lock;
int g_count = 0;

void* Write(void *arg)
{
    (void)arg;

    while(1){
        pthread_rwlock_wrlock(&g_lock);
        ++g_count;
        printf("write: %d\n", g_count);
        pthread_rwlock_unlock(&g_lock);
        usleep(789123);
    }
}

void* Read(void *arg)
{
    (void)arg;

    while(1){
        pthread_rwlock_rdlock(&g_lock);
//        ++g_count;
        printf("read: %d\n", g_count);
        pthread_rwlock_unlock(&g_lock);
        usleep(123456);
    }
}

int main()
{
    pthread_t tid[8];

    size_t i = 0;
    for (; i < 2; ++i){
        pthread_create(&tid[i], NULL, Write, NULL);
    }

    for (i = 2; i < 8; ++i){
        pthread_create(&tid[i], NULL, Read, NULL);
    }

    for (i = 0; i < 8; ++i){
        pthread_join(tid[i], NULL);
    }
   return 0;
}

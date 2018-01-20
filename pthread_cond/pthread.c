#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_cond_t g_cond;
pthread_mutex_t g_lock;

void* Entry1(void *arg)
{
    (void)arg;
    while(1){
        printf("pass!\n");
        pthread_cond_signal(&g_cond);
        usleep(678123);
    }
}

void* Entry2(void *arg)
{
    (void)arg;
    while(1){
        pthread_cond_wait(&g_cond, &g_lock);
        printf("shoot!\n");
        usleep(123456);
    }
}

int main()
{
    pthread_cond_init(&g_cond, NULL);
    pthread_mutex_init(&g_lock, NULL);

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, Entry1, NULL);
    pthread_create(&tid2, NULL, Entry2, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    pthread_cond_destroy(&g_cond);
    pthread_mutex_destroy(&g_lock);
    return 0;
}

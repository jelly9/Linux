#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <condition_variable>

void ThtreadEntry(int a, int b, std::mutex *lock)
{
    while(1){
        std::lock_guard<std::mutex> guard(*lock);
        printf("Thread: %d, %d\n", a, b);
        usleep(1000*500);
    }
}

int main()
{
    int a = 10;
    int b = 20;

    std::mutex lock;
    std::thread t(ThtreadEntry, a, b, &lock);

    t.join();
    return 0;
}


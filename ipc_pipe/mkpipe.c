#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{

    int ret = mkfifo("mypipe", 0666);
    if(ret < 0){
        perror("mkfifo");
        return 1;
    }

    printf("mkfifo OK!\n");
  
    return 0;
}

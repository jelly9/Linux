#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main()
{
    int i = 0;
    pid_t ret = vfork();

    if(ret < 0){
        perror("fork");
        return 1;
    }
    else if(ret > 0){//father
        printf("father start!\n");
        printf("%p: %d\n", &i, i);
        printf("father end\n");
    }else{//child
        printf("child start!\n");
        ++i;
        printf("%p: %d\n", &i, i);
        sleep(5);
        printf("child end\n");
        exit(0);
    }

    return 0;
}

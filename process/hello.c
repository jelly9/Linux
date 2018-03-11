#include <stdio.h>

int main(int argc, char *argv[], char *env[])
{
    int i = 0;
    for(; i < argc; i++){
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    int j = 0;
    while(env[j]){
        printf("%s\n", env[j]);
        j++;
    }

    return 0;
}

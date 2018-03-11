
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main()
{
    const char *path= "./hello";
    char* const arg[] = {"aaa", "bbb", "ccc", NULL};
    char* const env[] = {"MYENV=myenv", NULL};
    execv(path, arg, env);

    return 0;
}


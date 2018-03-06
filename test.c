#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("fd: %d -> %s\n", 0, ttyname(0));
    printf("fd: %d -> %s\n", 1, ttyname(1));
    printf("fd: %d -> %s\n", 2, ttyname(2));
    return 0;
}

#include <stdio.h>
#include "common.h"

int main()
{
    int msg_id = GetMsg();
    printf("msg_id = %d\n",  msg_id);

    return 0;
}
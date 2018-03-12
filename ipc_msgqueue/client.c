#include <stdio.h>
#include "common.h"

int main()
{
    int msg_id = GetMsg();
    printf("msg_id = %d\n",  msg_id);

    char rcvBuf[1024];
    char sndBuf[1024];
    while(1){
        read(0, sndBuf, 1024);
        SendMsg(msg_id, SERVER_TYPE, sndBuf);
        printf("server say: %s", rcvBuf);
        RecvMsg(msg_id, CLIENT_TYPE, rcvBuf);
    }

    return 0;
}

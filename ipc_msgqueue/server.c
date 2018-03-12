#include <stdio.h>
#include "common.h"

int main()
{
    int msg_id = CreateMsg();
    printf("msg_id = %d\n", msg_id);

    char rcvBuf[1024];
    char sndBuf[1024];
    while(1){
        RecvMsg(msg_id, CLIENT_TYPE, rcvBuf);
        printf("client say: %s", rcvBuf);
        read(0, sndBuf, 1024);
        SendMsg(msg_id, SERVER_TYPE, sndBuf);
    }

    return 0;
}

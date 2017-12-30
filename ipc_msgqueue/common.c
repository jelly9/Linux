#include "common.h"
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>

#define PATHNAME "."
#define PROJ_ID 0x99

int CommonMsg(int msgflg)
{
    key_t key = ftok(PATHNAME, PROJ_ID);
    if(-1 == key){//create failed!
        perror("ftok");
        return -1;
    }

    int msg_id = msgget(key, msgflg);
    if(msg_id < 0){ 
        perror("msgget");
        return -1;
    }

    return msg_id;
}



int CreateMsg()
{
    //if exist,return -1, else craete massege queue
    return CommonMsg(IPC_CREAT | IPC_EXCL | 0666);
}

int GetMsg()
{
    //if exist,return msg_id, else craete massege queue
    return CommonMsg(IPC_CREAT);
}

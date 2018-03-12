#include "common.h"

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

int DestroyMsg(int msg_id)
{
    if(msgctl(msg_id, IPC_RMID, NULL) <0){
        perror("msgctl");
        return -1;
    }

    return 0;
}

int SendMsg(int msg_id, int type, char *msg)
{
    struct msgbuf mb;
    mb.mtype = type;
    strcpy(mb.mtext, msg);
    if(msgsnd(msg_id, &mb, sizeof(mb.mtext), 0) < 0){
        perror("msgsnd");
        return -1;
    }
    return 0;
}

int RecvMsg(int msg_id, int type, char *out)
{
    struct msgbuf mb;

    if(msgrcv(msg_id, &mb, sizeof(mb.mtext), type, 0)<0){
        perror("msgrcv");
        return -1;
    }
    strcpy(out, mb.mtext);

    return 0;
}

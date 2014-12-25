#ifndef TRANSMITORSIMU_H
#define TRANSMITORSIMU_H
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#define MSGSZ     128


/*
 * Declare the message structure.
 */

typedef struct msgbuf {
         long    mtype;
         char    mtext[MSGSZ];
         } message_buf;



message_buf sbuf;
int msqid;
int msgflg = IPC_CREAT | 0666;
size_t buf_length;

int TranSimu_send(char* message);
int TranSimu_init(key_t key); //Transimu_init ,return msqid;
int TranSimu_dirsend(key_t key,char* message);
int Transimu_rec(char *message);
int Transimu_recLoop(int sleepTime);

#endif
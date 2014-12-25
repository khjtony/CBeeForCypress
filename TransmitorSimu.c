#include "TRANSMITORSIMU.h"

int TranSimu_init(key_t key){
    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        return 1;
    }
    else {
     (void) fprintf(stderr,"msgget: msgget succeeded: msqid = %d\n", msqid);
    }
    return 0;
} //Transimu_init 

int TranSimu_send(char* message){
    sbuf.mtype = 1;
    message_buf sbuf;
    if (strlen(message) > 127){
        strncpy(sbuf.mtext, message, 127);
        buf_length = 127;
    }
    else{
        strcpy(sbuf.mtext, message);
        buf_length = strlen(message) + 1;
    }
    if (msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT) < 0) {
       printf ("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
        perror("msgsnd");
        return 1;
    }
   else {
      printf("Message: \"%s\" Sent\n", sbuf.mtext);
   }
   return 0;
}

int TranSimu_dirsend(key_t key, char* message){
    if(TranSimu_init(key)){
        return 1;
    }
    if(TranSimu_send(message)){
        return 1;
    }
    return 0;
}


int Transimu_rec(char *message){
    if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }
    strcpy(message,rbuf.mtext);
    return 0;
}

int Transimu_recLoop(int sleepTime){
    char message[MSGSZ];
    while(1){
        Transimu_rec(message);
        printf("%s\n, message");
        sleep(sleepTime);
    }
    return 0;
}
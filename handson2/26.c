/*
============================================================================
Name : 26.c
Author : Smit Mehta
Description : Write a program to send messages to the message queue.
Date: 14th oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    int msqid;
    key_t key;
    struct msgbuf message;

    key = ftok("/tmp", 20); 

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msqid = msgget(key, 0666 | IPC_CREAT);

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    message.mtype = 1; 
    strcpy(message.mtext, "New Message");


    if (msgsnd(msqid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("Message send : %s",message.mtext);

    return 0;
}
/*
============================================================================
Name : 28.c
Author : Smit Mehta
Description : Write a program to change the exiting message queue permission.
Date: 14th oct, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    int msqid;
    key_t key;
    struct msqid_ds queueInfo;


    key = ftok("/tmp", 20);

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msqid = msgget(key, 0666);

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    if (msgctl(msqid, IPC_STAT, &queueInfo) == -1) {
        perror("msgctl IPC_STAT");
        exit(1);
    }

    queueInfo.msg_perm.mode =0777;
    
    if (msgctl(msqid, IPC_SET, &queueInfo) == -1) {
        perror("msgctl IPC_SET");
        exit(1);
    }

    printf("Message queue permissions updated successfully.\n");

    return 0;
}
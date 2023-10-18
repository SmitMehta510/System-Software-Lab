/*
============================================================================
Name : 24.c
Author : Smit Mehta
Description : Write a program to create a message queue and print the key and message queue id.
Date: 12th oct, 2023.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    key = ftok("/tmp", 20);

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
                             
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}
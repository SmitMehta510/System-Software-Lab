/*
============================================================================
Name : 29.c
Author : Smit Mehta
Description : Write a program to remove the message queue
Date: 30th sept, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main(int argc, char const *argv[])
{	
	key_t key;
	int msqid;

	if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

	key = ftok("/tmp",20);	

	msqid = msgget(key,IPC_CREAT|0666);

	if (msqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

	if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

	printf("Message queue removed successfully.\n");

	return 0;
}
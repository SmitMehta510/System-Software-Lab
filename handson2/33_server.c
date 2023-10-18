/*
============================================================================
Name : 33_server.c
Author : Smit Mehta
Description : Write a program to communicate between two machines using socket.
Date: 8th oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

void tcpData(){

    int listensd;       // Listen socket descriptor
    int connectsd;      // Connecting socket descriptor
    int len;
    int processId;      //process ID of child process

    struct sockaddr_in sin;

    /*Creating new socket,AF_INET/PF_INET can be used interchangeably to
     indicate socket will be used for IPv4 communication.SOCK_STREAM is used for TCP connection, 
    0 is given as protocol value for TCP/IP protocol suite*/
    if ((listensd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
            perror("simplex-talk: socket");
            exit(1);
    }

    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(5432); 
    if ((bind(listensd, (struct sockaddr *)&sin, sizeof(sin))) < 0){
            perror("simplex-talk: bind");
            exit(1);
    }
    else{
            printf("Server bind done.\n");
    }

    listen(listensd, 5);
    char string[10];
    int choice = -1;

    while (1){
        if ((connectsd = accept(listensd, (struct sockaddr *)&sin, &len)) < 0) {
            perror("simplex-talk: accept\n");
            exit(1);
        }

        processId = fork();

        char ques[300],buffer[100];

        while (1)
        {
            scanf("%s",buffer);
            send(connectsd,&buffer,strlen(buffer),0);
            memset(&buffer,0,sizeof(buffer));
            
            recv(connectsd,&ques,sizeof(ques),0);
            printf("%s\n",ques);
            memset(&ques,0,sizeof(ques));

        }
        

    }
}

int main(int argc, char const *argv[])
{
    tcpData();
    return 0;
}
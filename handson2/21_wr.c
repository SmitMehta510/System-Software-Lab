/*
============================================================================
Name : 21_wr.c
Author : Smit Mehta
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 9th oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() 
{
    int file = open("fifo1", O_RDWR);
    char message[100];
    scanf("%s",message);
    write(file, &message, strlen(message));
    char response[100];
    int bytesRead = read(file, response, sizeof(response));
    printf("%s\n", response);
    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
    return 0;
}
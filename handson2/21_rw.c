/*
============================================================================
Name : 21_rw.c
Author : Smit Mehta
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 9th oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() 
{
    int file = open("fifo1", O_RDWR);

    char message[100];
    int bytesRead = read(file, message, sizeof(message));
    write(1, message, bytesRead);
    printf("\n");
    char response[100];
    scanf("%s",response);
    write(file, response, sizeof(response));
    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
    return 0;
}
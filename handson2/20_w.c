/*
============================================================================
Name : 20_w.c
Author : Smit Mehta
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 9th oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int file = open("fifo1",O_WRONLY);
    char buff[100];

    printf("Enter the message");
    scanf("%[^\n]",&buff);
    write(file,&buff,strlen(buff));
    return 0;
}

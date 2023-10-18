/*
============================================================================
Name : 20_r.c
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
    int file = open("fifo1",O_RDONLY);
    char buff[100];

    read(file,buff,sizeof(buff));
    write(1,buff,strlen(buff));
    return 0;
}

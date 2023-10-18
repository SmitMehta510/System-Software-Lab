/*
============================================================================
Name : 22_w.c
Author : Smit Mehta
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 9th oct, 2023.
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() 
{
    int file = open("fifo1", O_WRONLY);
    char message[100];
    scanf("%s",message);
    write(file, &message, strlen(message));
    return 0;
}
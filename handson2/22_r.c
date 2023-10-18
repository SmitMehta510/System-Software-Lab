/*
============================================================================
Name : 22_r.c
Author : Smit Mehta
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select
system call with FIFO.
Date: 9th oct, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

	fd_set rfds;
	struct timeval tv;
	int val;

    int file = open("fifo1", O_RDONLY);
    char buff[50];
	FD_ZERO(&rfds);
	FD_SET(file,&rfds);

	tv.tv_sec = 10;
    tv.tv_usec = 0;

    if (!select(file + 1, &rfds, NULL, NULL, &tv))
        printf("No data is available for reading yet\n");
    else {
        printf("Data is available now\n");
        read(file, buff, sizeof(buff));
        printf("Data: %s\n", buff);
    }
	return 0;
}
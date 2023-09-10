/*
============================================================================
Name : 10.c
Author : Smit Mehta
Description : C program to implement lseek functionality.
Date: 25th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{	
	int file = open("test.txt",O_RDWR);
	char buff[]="Thisistestdata";

	int datawrite= write(file, &buff, 10);
	if(datawrite==-1){
		printf("error writing to the file");
	}
	int seekinfo = lseek(file,10,SEEK_SET);
	printf("Seek returned %d\n", seekinfo);

	char buff1[] ="changedData";

	int datawrite1= write(file, &buff1, 10);
	if(datawrite==-1){
		printf("error writing to the file");
	}

	int fd_close = close(file);
	if(fd_close == -1){
		printf("Error closing file");
	} 

	return 0;
}
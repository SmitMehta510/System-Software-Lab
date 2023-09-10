/*
============================================================================
Name : 11.c
Author : Smit Mehta
Description : C program to implement dup, dup2 and using fcntl to duplicate
		 file descriptors and manipulate the file.
Date: 25th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

	int file = open("newtestfile.txt",O_RDWR);
	int duplicate = dup(file);
	int newfile;
	int duplicate1 = dup2(file, newfile);
	int fcntldup = fcntl(file,F_DUPFD);

	char buff[100];
	printf("Reading from file descriptor\n");	
	int dataRead = read(file, buff, 10);
	int dataWrite = write(1,buff,10);

	printf("\n");

	if(dataRead == -1 || dataWrite == -1 ){
		printf("Error");
	}

	printf("Reading from fcntl duplicate file descriptor\n");
	dataRead = read(fcntldup, buff, 10);
	dataWrite = write(1,buff,10);

	printf("\n");

	printf("Reading from and appending to (dup)duplicate file descriptor\n");
	dataRead = read(duplicate, buff, 10);
	dataWrite = write(1,buff,10);
	int dataappend = write(duplicate,buff,10);

	printf("\n");

	printf("Reading from (dup2)duplicate file descriptor\n");
	dataRead = read(duplicate1, buff, 10);
	dataWrite = write(1,buff,10);

	int fd_close1 = close(file);
	int fd_close2 = close(duplicate);
	int fd_close3 = close(duplicate1);

	if(fd_close1 == -1 || fd_close2 == -1 || fd_close3 == -1){
		printf("Error closing files");
	} 

	return 0;
}
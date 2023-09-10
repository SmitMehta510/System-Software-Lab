/*
============================================================================
Name : 14.c
Author : Smit Mehta
Description : C program to find the type of a file in linux.
Date: 25th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

	struct stat filestat;
	int fd_read = open(argv[1],O_RDONLY);

	getchar();
	getchar();
	if(fd_read == -1){
		printf("Error opening files");
	} 
	stat(fd_read,&filestat);

	int mode = filestat.st_mode;

	if(S_ISREG(mode)){
		printf("Given file is a Regular file\n");
	}else if(S_ISBLK(mode)){
		printf("Given file is a Block special file\n");
	}else if(S_ISCHR(mode)){
		printf("Given file is a character special file\n");
	}else if(S_ISDIR(mode)){
		printf("Given file is a Directory\n");
	}else if(S_ISFIFO(mode)){
		printf("Given file is FIFO special file\n");
	}else if(S_ISLNK(mode)){
		printf("Given file is symbolic link\n");
	}
	return 0;
}
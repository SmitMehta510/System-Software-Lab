/*
============================================================================
Name : 7.c
Author : Smit Mehta
Description : C program to copy contents of file1 into file2 using read 
		and write system calls.
Date: 25th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[]){

	if(argc !=3){
		printf("Error. Incorrect number of arguments");
		return 0;
	}

	int fd_read = open(argv[1],O_RDONLY);
	int fd_write = open(argv[2],O_WRONLY|O_CREAT);
	if(fd_read == -1 || fd_write == -1){
		printf("Error opening files");
	} 
	while(1){
		char buff;
		int charRead = read(fd_read,&buff,1);
		if(charRead==0){
			break;
		}
		int charReturned = write(fd_write,&buff,1);
	}
	
	int fd_read_close = close(fd_read);
	int fd_write_close = close(fd_write);
	if(fd_read_close == -1 || fd_write_close == -1){
		printf("Error closing files");
	} 
	
	return 0;
}

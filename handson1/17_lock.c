/*
============================================================================
Name : 17.c
Author : Smit Mehta
Description : C program to simulate online ticket resevation by using Locking. 
Date: 29th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

	struct Ticketdata{
		int ticketno;
	};

	int file = open("ticketinfo.txt",O_RDWR);

	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len =0;
	lock.l_pid = getpid();

	printf("Before taking write lock on the file\n");
	fcntl(file,F_SETLKW,&lock);

	struct Ticketdata tdata;

	int seekinfo = lseek(file,0,SEEK_SET);
	int dataRead = read(file,&tdata,sizeof(struct Ticketdata));
	//printf("read ticketno %d\n",tdata.ticketno);
	tdata.ticketno++;
	seekinfo = lseek(file,0,SEEK_SET);
	int datawrite = write(file,&tdata,sizeof(struct Ticketdata));
	printf("New ticket number is %d\n",tdata.ticketno);

	getchar();

	lock.l_type = F_UNLCK;
	fcntl(file,F_SETLKW,&lock);
	printf("File unlocked\n");

	int fileclose = close(file);
	if(fileclose == -1){
		printf("Error closing file");
	}

	return 0;
}
/*
============================================================================
Name : 18.c
Author : Smit Mehta
Description : C program to implement record locking in the online 
				train reservation stem simulation.
Date: 29th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>

struct Ticketinfo{
	int trainno;
	int ticketno;
};

void readLockImpl(int len,int file){

	printf("Enter train number (1-3)\n");
	int trainno;
	scanf("%d",&trainno);

	int offset = trainno - 1;

	struct flock readlock;
	readlock.l_type = F_RDLCK;
	readlock.l_whence = SEEK_SET;
	readlock.l_start = offset*len;
	readlock.l_len = len;
	readlock.l_pid = getpid();

	printf("Taking read lock on data for %d train\n",trainno);
	fcntl(file,F_SETLKW,&readlock);


	struct Ticketinfo tinfo; 
	int seekinfo = lseek(file,offset*len,SEEK_SET);
	int dataread = read(file,&tinfo,len);
	printf("Current train info\n");
	printf("Train Number = %d\n",tinfo.trainno);
	printf("Ticket number = %d\n",tinfo.ticketno);
	printf("Press enter to continue\n");
	getchar();
	getchar();

	readlock.l_type = F_UNLCK;
	fcntl(file,F_SETLKW,&readlock);
	printf("Unlocked data for %d train\n",trainno);	
}

void writeLockImpl(int len,int file){

	printf("Enter train number (1-3)\n");
	int trainno;
	scanf("%d",&trainno);

	int offset = trainno - 1;

	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = offset*len;
	lock.l_len = len;
	lock.l_pid = getpid();

	printf("Taking write lock on data for %d train\n",trainno);
	fcntl(file,F_SETLKW,&lock);

	struct Ticketinfo tinfo; 
	int seekinfo = lseek(file,offset*len,SEEK_SET);
	int dataread = read(file,&tinfo,len);
	tinfo.ticketno++;
	seekinfo = lseek(file,offset*len,SEEK_SET);
	int datawrite = write(file,&tinfo,len);
	printf("Updated train info after reservation\n");
	printf("Train Number = %d\n",tinfo.trainno);
	printf("Ticket number = %d\n",tinfo.ticketno);
	printf("Press enter to confirm\n");
	getchar();
	getchar();

	lock.l_type = F_UNLCK;
	fcntl(file,F_SETLKW,&lock);
	printf("Unlocked data for %d train\n",trainno);

	
}

int main(int argc, char const *argv[])
{

	int file = open("traindata.txt",O_RDWR|O_CREAT);

	int choice =0;

	printf("1.View train and ticket information\n");
	printf("2.Book ticket\n");
	scanf("%d",&choice);

	int len = sizeof(struct Ticketinfo);

	switch(choice){
	case 1:
		readLockImpl(len,file);
		break;
	case 2:
		writeLockImpl(len,file);
		break;
	default:
		printf("Invalid choice\n");
		exit(0);
	}
	
	int fileclose = close(file);
	if(fileclose == -1){
		printf("Error closing file");
	}

	return 0;
}

/*
============================================================================
Name : 1.c
Author : Smit Mehta
Description : C program to create sotlink, hardlink and FIFO 
		types of files
Date: 17th Aug, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(){
	int v = symlink("dest.txt","destSymLink2");
	if(v<0)
	{
		perror("Failed");
		return 1;
	}
	
	int f = link("dest.txt","destHardLink2");
	if(f<0)
	{
		perror("Failed");
		return 1;
	}
	
	int e = mknod("destFIFO",S_IFIFO,0);
	if(f<0)
	{
		perror("Failed");
		return 0;
	}
}

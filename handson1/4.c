/*
============================================================================
Name : 4.c
Author : Smit Mehta
Description : C program to open an existing file in read write mode
Date: 17th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	int x = open("dest.txt",O_RDWR);
	
	if(x<0){
		perror("failed");
		return 1;
	}
	
	close(x);
	return 1;
}

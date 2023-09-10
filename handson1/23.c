/*
============================================================================
Name : 23.c
Author : Smit Mehta
Description : C program to create zombie state of process.
Date: 8th Sept, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
	if(fork() == 0){
		printf("child process id = %d\n", getpid());
		exit(0);
	}else{
		sleep(20);
		printf("parent process id = %d\n", getpid());
	}
	return 0;
}
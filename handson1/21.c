/*
============================================================================
Name : 21.c
Author : Smit Mehta
Description : C program to create child process by using fork system call.
Date: 8th Sept, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
	if(fork() == 0){
		printf("child process id = %d\n", getpid());
		printf("child's parent process id = %d\n", getppid());
	}else{
		printf("parent process id = %d\n", getpid());
		printf("parent's parent process id = %d\n", getppid());
	}
	return 0;
}
/*
============================================================================
Name : 25.c
Author : Smit Mehta
Description : C program to create 3 child process using fork and use waitpid
	 system call for parent to wait for child execution to be completed.
Date: 8th Sept, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t ch1,ch2,ch3,parent;
	int wstatus;
	ch1 = fork();
	if(ch1 ==0){
		printf("Child 1 pid: %d\n",getpid());
		printf("Child 1 ppid: %d\n",getppid());
	}
	else
	{
		waitpid(-1,&wstatus,0);
		ch2 = fork();
		if(ch2==0)
		{
			printf("Child 2 process id: %d\n",getpid());
			printf("Child 2 ppid: %d\n",getppid());
		}
		else
		{
			waitpid(-1,&wstatus,0);
			ch3 = fork();
			if(ch3==0)
			{
				printf("Child 3 process id: %d\n",getpid());
				printf("Child 3 ppid: %d\n",getppid());
			}
			else
			{
				waitpid(-1,&wstatus,0);
				printf("parent process id: %d\n",getpid());
				printf("parent ppid: %d\n",getppid());
			}
		}
	}
	
	return 0;
}

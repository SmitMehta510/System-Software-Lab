/*
============================================================================
Name : 20.c
Author : Smit Mehta
Description : C program to find priority of the program and modify priority
		 with nice command
Date: 8th Sept, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/resource.h>

int main(int argc, char const *argv[])
{

	int priority = getpriority(PRIO_PROCESS,0);
	printf("old priority= %d\n",priority);
	int nicevalue = nice(10);
	priority = getpriority(PRIO_PROCESS,0);
	printf("new priority = %d\n",priority);
	return 0;
}
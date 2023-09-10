/*
============================================================================
Name : 15.c
Author : Smit Mehta
Description : C program to display the environmental variable using environ.
Date: 25th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	extern char **environ;
	int i = 0;
	while(environ[i]) {
	  printf("%s\n", environ[i++]);
	}
}
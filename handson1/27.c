/*
============================================================================
Name : 27.c
Author : Smit Mehta
Description : C program to execute ls -Rl command using different exec system calls.
Date: 8th Sept, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

	char *path = "/bin/ls";
	char *arg1 = "-Rl";
	char *arg2 = "/home/smit/sslab";

	const char *file ="/bin/ls";

	extern char **environ;

	printf("1. execl\n");
	printf("2. execlp\n");
	printf("3. execle\n");
	printf("4. execv\n");
	printf("5. execvp\n");
	int choice;
	scanf("%d",&choice);

	switch(choice){
	case 1:
		execl(path,path,arg1,arg2,NULL);
		break;
	case 2:
		execlp(file,file,arg1,arg2,NULL);	
		break;
	case 3:
		execle(path,path,arg1,arg2,NULL,environ);
		break;
	case 4:
		execv(path,argv);
		break;
	case 5: 
		execvp(file,argv);
		break;
	default:
		exit(0);	
	}

	return 0;
}
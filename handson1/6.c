/* 
============================================================================
Name : 6.c
Author : Smit Mehta
Description : C program to take input and show output using read and write system call.
Date: 25th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{

	char buff[20];
	int dataRead = read(0,buff,20);
	int dataWrite = write(1,buff,20);

	if(dataRead == -1 || dataWrite == -1 ){
		printf("Error");
	}
	return 0;
}
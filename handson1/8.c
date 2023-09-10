/*
============================================================================
Name : 8.c
Author : Smit Mehta
Description : C program to read from a file line by line and display 
		each line after reading.
Date: 25th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	
	int file = open("dest.txt",O_CREAT|O_RDONLY);

	int dataread=1,datawrite;
	while(dataread!=0){
			char buff[1];
			while((int)buff !=10){
				dataread = read(file,buff, 1);
				if(dataread == 0){
					buff[0]='~';
					break;
				}
				datawrite = write(1,buff,1);
			}
	}

	close(file);


	return 0;
}
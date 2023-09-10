/*
============================================================================
Name : 30.c
Author : Smit Mehta
Description : C program to create a new daemon process and running a script 
		from the process at a specific given time.
Date: 8th Sept, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<time.h>
#include<fcntl.h>


int main(void)
{
	int file = open("log.txt",O_RDWR|O_CREAT);
    struct tm exectime;
    exectime.tm_hour = 10;
	exectime.tm_min = 19;
	exectime.tm_sec = 1;

	char buff[] = "Running job from daemon process";
	
	if(fork()==0){
		setsid();
		umask(0);
		chdir("/");
		while(1){
		    time_t timevalue = time(NULL);
		    struct tm* currtime = localtime(&timevalue);

		    if(currtime->tm_hour == exectime.tm_hour && currtime->tm_min == exectime.tm_min 
		    	&& currtime->tm_sec == exectime.tm_sec){

				write(file,buff,sizeof(buff));
		    
		    break;
		}
	}
	}else{
		exit(0);
	}
    return 0;
}

	

			    	




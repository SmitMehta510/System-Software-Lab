/*
============================================================================
Name : 29.c
Author : Smit Mehta
Description : C program to get current scheduling policy and modifing 
		the scheduling policy.
Date: 8th Sept, 2023.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include <sched.h>

int main(int argc, char const *argv[])
{

	struct sched_param {
		int sched_priority;
	};

	struct sched_param param;

	pid_t pid = getpid();
	int value = sched_getscheduler(pid);

	switch(value) {
	    case SCHED_OTHER:
	    	printf("Scheduling policy is SCHED_OTHER\n");
	    	break;
	    case SCHED_FIFO:
      		printf("Scheduling policy is SCHED_FIFO\n");
      		break;
	    case SCHED_RR:
      		printf("Scheduling policy is SCHED_RR\n");
      		break;
	    default:
	       	printf("Appropriate scheduling policy not found\n");
  	}

	param.sched_priority = 5;
	int value2 =  sched_setscheduler( 0, SCHED_RR, &param );
	if (value2 == -1){
		printf("Error setting scheduler");
	}


	value = sched_getscheduler(pid);
	switch(value) {
	    case SCHED_OTHER:
	    	printf("Scheduling policy is SCHED_OTHER\n");
	    	break;
	    case SCHED_FIFO:
      		printf("Scheduling policy is SCHED_FIFO\n");
      		break;
	    case SCHED_RR:
      		printf("Scheduling policy is SCHED_RR\n");
      		break;
	    default:
	       	printf("Appropriate scheduling policy not found\n");
  	}

	return 0;
}
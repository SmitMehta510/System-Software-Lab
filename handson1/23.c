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
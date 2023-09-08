#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
	if(fork() == 0){
		sleep(10);
		printf("child process id = %d\n", getpid());
		printf("child's parent process id = %d\n", getppid());
	}else{
		printf("parent process id = %d\n", getpid());
		exit(0);
	}
	return 0;
}
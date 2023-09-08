#include<stdio.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
	if(fork() == 0){
		printf("child process id = %d\n", getpid());
		//printf("child's parent process id = %d\n", getppid());
	}else{
		printf("parent process id = %d\n", getpid());
		//printf("parent's parent process id = %d\n", getppid());
	}
	return 0;
}
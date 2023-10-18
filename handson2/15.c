#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include<string.h>

//one-way communication
int main(int argc, char const *argv[])
{
	int fd[2];
	char buff[80] = {'\0'};
	pipe(fd);
	pid_t childid;

	childid = fork();

	if(childid == 0){
		close(fd[1]);
		while(read(fd[0],&buff,1)>0){
			int charReturned = write(1,&buff,1);
		}
		printf("\n");
		close(fd[0]);
	}else{
		close(fd[0]);
		scanf("%[^\n]",buff);
		write(fd[1],buff,strlen(buff));
		close(fd[1]);
		wait(NULL);
	}

	return 0;
}

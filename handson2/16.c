#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>

//one-way communication
int main(int argc, char const *argv[])
{
	int fd1[2],fd2[2];
	char buff[80] ={'\0'};
	char buff1[80] ={'\0'};
	pipe(fd1);
	pipe(fd2);
	pid_t childid;

	childid = fork();

	if(childid == 0){
		//writing from parent
		//printf("printing from child, %d, with ppid %d\n",getpid(),getppid());
		close(fd1[1]);
		while(read(fd1[0],&buff,1)>0){
			int charReturned = write(1,&buff,1);
		}
		printf("\n");
		close(fd1[0]);
		//writing from child
		close(fd2[0]);
		//printf("Child %d . Enter message for parent.\n",getpid());
		scanf("%[^\n]",buff1);
		write(fd2[1],buff1,sizeof(buff1));
		close(fd2[1]);
	}else{
		//writing from parent
		close(fd1[0]);
		//printf("Parent %d . Enter message for child.\n",getpid());
		scanf("%[^\n]",buff);
		write(fd1[1],buff,sizeof(buff));
		close(fd1[1]);

		//reading from parent
		//printf("printing from parent, %d, with ppid %d\n",getpid(),getppid());
		close(fd2[1]);
		while(read(fd2[0],&buff1,1)>0){
			int charReturned = write(1,&buff1,1);
		}
		printf("\n");
		close(fd2[0]);
		wait(NULL);
	}
	
	return 0;
}

#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int file = open("22.txt",O_CREAT|O_RDWR);

	if(fork()==0){
		char *buff ="Writing data from child process";
		int datawrite = write(file,buff,30);
		if(datawrite==-1){
			printf("Error writing to file");
		}
	}else{
		char *buff ="Writing data from parent process";
		int datawrite = write(file,buff,30);
		if(datawrite==-1){
			printf("Error writing to file");
		}
	}

	int dataread = -1,datawrite=-1;
	int seekinfo = lseek(file,0,SEEK_SET);
	while(1){
		char buff;
		int charRead = read(file,&buff,1);
		if(charRead==0){
			break;
		}
		int charReturned = write(1,&buff,1);
	}
	printf("\n");
	int fileclose = close(file);
	if(fileclose == -1){
		printf("Error closing file");
	}
	return 0;
}
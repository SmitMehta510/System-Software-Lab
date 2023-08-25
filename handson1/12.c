#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int file = open("dest.txt",O_CREAT|O_RDWR);

	int value = fcntl(file,F_GETFL);
	int answer = value & O_ACCMODE;
	
	if(answer==0){
		printf("File opening mode is Read mode");
	}else if(answer == 1){
		printf("File opening mode is write mode");
	}else if (answer ==2){
		printf("File opening mode is read-write mode");
	}

	int fd_close = close(file);
	if(fd_close == -1){
		printf("Error closing file");
	}
	return 0;
}
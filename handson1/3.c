#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	const char *file_name ="newfile";
	int x = creat(file_name,O_CREAT);
	
	printf("File descriptor value = %d",x);
	
	if(x<0){
		perror("Error");
		return 1;
	}
	
	close(x);
	return 0;
	
}



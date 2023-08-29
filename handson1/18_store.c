#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

	struct Ticketinfo{
		int trainno;
		int ticketno;
	}tinfo[3];

	for(int i=0;i<3;i++){
		tinfo[i].trainno = i+1;
		tinfo[i].ticketno = 0;
	}

	int file = open("traindata.txt",O_RDWR|O_CREAT);
	if(file == -1){
		printf("Error opening file");
	}

	int datawrite = write(file,tinfo,sizeof(tinfo));
	if(datawrite == -1){
		printf("Error writing to file");
	}

	int fileclose = close(file);
	if(fileclose == -1){
		printf("Error cloding file");
	}
	return 0;	
}
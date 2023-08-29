#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

	struct Ticketdata{
		int ticketno;
	};

	struct Ticketdata tinfo;
	tinfo.ticketno = 100;

	int file = open("ticketinfo.txt",O_RDWR);
	if(file == -1){
		printf("Error opening file");
	}

	int data_write = write(file,&tinfo,sizeof(struct Ticketdata));
	printf("Ticket number is %d\n", tinfo.ticketno);
	if(data_write == -1){
		printf("Error writing to file");
	}

	int fileclose = close(file);
	if(fileclose == -1){
		printf("Error closing file");
	}

	return 0;
}
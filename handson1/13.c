#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

	fd_set rfds;
	struct timeval tv;
	int val;

	FD_ZERO(&rfds);
	FD_SET(0,&rfds);

	tv.tv_sec = 10;
    tv.tv_usec = 0;

    val = select(2,&rfds,NULL,NULL,&tv);

    if (val == -1)
		perror("Error occured");
	else if (val)
		printf("Data available to read");
	else
		printf("No data was available to read within 10 seconds.\n");
	
	return 0;
}
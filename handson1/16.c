#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>

void readLockImpl(int file){
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len =0;
	lock.l_pid = getpid();

	printf("Locking the file with read lock\n");
	fcntl(file,F_SETLKW,&lock);

	while(1){
		char buff;
		int charRead = read(file,&buff,1);
		if(charRead==0){
			break;
		}
		int charReturned = write(1,&buff,1);
	}
	printf("File read complete. Press enter to continue\n");
	getchar();
	getchar();
	lock.l_type = F_UNLCK;
	fcntl(file,F_SETLKW,&lock);
	printf("File unlocked\n");
}

void writeLockImpl(int file){

	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len =0;
	lock.l_pid = getpid();

	//write lock implementation

	printf("Locking the file with write lock\n");
	fcntl(file,F_SETLKW,&lock);

	char buff[20];
	char data = "Adding new data";
	int dataread = read(file,buff,10);
	int datawrite = write(file,buff,10);
	printf("\n");
	dataread = read(file,buff,10);
	datawrite = write(1,buff,10);
	printf("\n");
	printf("Data written. Press enter to continue\n");
	getchar();
	getchar();
	lock.l_type = F_UNLCK;
	fcntl(file,F_SETLKW,&lock);
	printf("File unlocked\n");
}

int main(int argc, char const *argv[])
{

	int choice =0;

	printf("1.Read data\n");
	printf("2.Write data\n");
	scanf("%d",&choice);

	int file = open("dest.txt",O_RDWR);

	switch(choice){
	case 1:
		readLockImpl(file);
		break;
	case 2:
		writeLockImpl(file);
		break;
	default:
		printf("Invalid choice\n");
		exit(0);
	}

	int fileclose = close(file);
	if(fileclose == -1){
		printf("Error closing file\n");
	}

	return 0;
}
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>

int main(){

	int count =0;
	char name[20]; 
	while(1){
		if(count<5){
			sprintf(name, "newfile%d.txt",count);
			const char *file_name =name;
			int x = creat(file_name,O_CREAT);
			count++;
		}
	}
	return 0;
}

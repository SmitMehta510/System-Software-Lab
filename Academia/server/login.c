#include "../headers.h"

bool studentLogin(int Id,char* pass){
    int file = open("studentinfo.txt",O_RDWR | O_CREAT,0744);

    struct studentInfo sinfo;
    memset(&sinfo,0,sizeof(sinfo));

    int offset = (Id-1)*(sizeof(struct studentInfo));

    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&sinfo,sizeof(struct studentInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
	}
    if(Id == sinfo.ID){
        if(strcmp(sinfo.password,pass)==0){
            return true;
        }
    }

    return false;
}


bool facultyLogin(int Id,char* pass){
    int file = open("facultyinfo.txt",O_RDWR | O_CREAT,0744);

    struct facultyInfo finfo;
    memset(&finfo,0,sizeof(finfo));

    int offset = (Id-1)*(sizeof(struct facultyInfo));

    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&finfo,sizeof(struct facultyInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
	}
    if(Id == finfo.ID){
        if(strcmp(finfo.password,pass)==0){
            return true;
        }
    }

    return false;
}
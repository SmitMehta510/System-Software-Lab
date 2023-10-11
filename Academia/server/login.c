#include "../headers.h"
#include "structures.c"

// struct loginInfo
// {
//     int usertype;
//     char uname[20];
//     char password[20];
// };

bool login(int type,char name[], char pass[]){
//bool login(struct loginInfo linfo){
    int file = open("logininfo.txt",O_RDONLY | O_CREAT,0744);

    struct loginInfo info;
    int dataread;
    bool success = true;

    // printf("choice: %d\n",linfo.usertype);
    // printf("name : %s \n",linfo.uname);
    // printf("pass: %s \n",linfo.password);

    printf("choice: %d\n",type);
    printf("name : %s \n",name);
    printf("pass: %s \n",pass);
    while (1)
    {   
        dataread = read(file,&info,sizeof(struct loginInfo));
        if(dataread ==0){
            success = false;
            break;
        }
        printf("choice: %d\n",info.usertype == type);
        printf("%d \n",strcmp(info.uname,name));
        printf("%s \n",info.password);
        if(info.usertype == type  && strcmp(info.uname,name)==0 && strcmp(info.password,pass)==0){
            break;
        }
    }

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
	}

    return success;
}

void saveinfo(){
    int file = open("logininfo.txt",O_WRONLY | O_CREAT,0744);

    struct loginInfo info1;
    info1.usertype = 1;
    // strcpy(info1.uname,"Smit");
    // strcpy(info1.password,"1234");

    // struct loginInfo info2;
    // info2.usertype = 2;
    // strcpy(info2.uname,"Smit1");
    // strcpy(info2.password,"12345");

    read(0,info1.uname,sizeof(info1.uname));
    read(0,info1.password,sizeof(info1.password));
    write(file,&info1,sizeof(struct loginInfo));
    //write(file,&info2,sizeof(struct loginInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
	}
}
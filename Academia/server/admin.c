#include "../headers.h"

struct studentInfo
{
    int ID;
    char password[30];
    char name[30];
    int age;
    char email[50];
    char address[50];
    bool active;
};

struct facultyInfo
{
    int ID;
    char name[30];
    char password[30];
    char department[30];
    char designation[20];
    char email[50];   
};

void addStudent(int sd){
    int file = open("studentinfo.txt",O_WRONLY | O_CREAT,0744);
    struct studentInfo sinfo;
    memset(&sinfo,0,sizeof(sinfo));
    char buffer[60];

    char value ='4';
    send(sd,&value,sizeof(value),0);        //send total length of questions

    sinfo.ID =1;
    strcpy(sinfo.password,"dummy");
    sinfo.active = true;
    char msg1[] = "Enter student Name:";
    send(sd,&msg1,strlen(msg1),0);
    recv(sd,&buffer,sizeof(buffer),0);
    strcpy(sinfo.name,buffer);
    memset(&buffer,0,sizeof(buffer));

    char msg2[] = "Enter student Age:";
    send(sd,&msg2,strlen(msg2),0);
    recv(sd,&buffer,sizeof(buffer),0);
    sinfo.age = atoi(buffer);
    memset(&buffer,0,sizeof(buffer));
    
    char msg3[] ="Enter student Email:";
    send(sd,&msg3,strlen(msg3),0);
    recv(sd,&buffer,sizeof(buffer),0);
    strcpy(sinfo.email,buffer);
    memset(&buffer,0,sizeof(buffer));

    char msg4[] ="Enter student Address:";
    send(sd,&msg4,strlen(msg4),0);
    recv(sd,&buffer,sizeof(buffer),0);
    strcpy(sinfo.address,buffer);
    //memset(buffer, '\0', sizeof(buffer));
    //bzero(buffer,sizeof(buffer));
    
    lseek(file,0,SEEK_END);
    write(file,&sinfo,sizeof(struct studentInfo));
    printf("ID =%d\n",sinfo.ID);
    printf("name = %s\n",sinfo.name);
    printf("active = %d",sinfo.active);
    printf("password = %s\n",sinfo.password);
    printf("age =%d\n",sinfo.age);
    printf("email =%s\n",sinfo.email);
    printf("add =%s\n",sinfo.address);

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
	}
}

void viewAllStudentDetails(int sd){


    int file = open("studentinfo.txt",O_RDONLY | O_CREAT,0744);
    // struct studentInfo stuinfo;
    // int seekinfo = lseek(file,offset,SEEK_SET);
    // int dataRead = read(file,&stuinfo,sizeof(struct studentInfo));
    
    // printf("details are\n");

    // printf("ID = %d\n",stuinfo.ID);
    // printf("name = %s\n",stuinfo.name);
    // printf("age =%d\n",stuinfo.age);
    // printf("email =%s\n",stuinfo.email);
    // printf("add =%s\n",stuinfo.address);


    int offset =0;
    int len = sizeof(struct studentInfo);
    while(1){
		struct studentInfo info; 
		int seekinfo = lseek(file,offset,SEEK_SET);
		int dataread = read(file,&info,len);
		if(dataread == 0){
			break;
		}
		printf("Student Id : %d \n",info.ID);
		printf("name: %s\n",info.name);
        printf("age: %d\n",info.age);
        printf("email: %s\n",info.email);
        printf("address: %s\n",info.address);
		offset+=len;
	}

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
    
}

void viewStudentDetails(int sd){
    int file = open("studentinfo.txt",O_RDONLY | O_CREAT,0744);
    char value ='2';
    send(sd,&value,sizeof(value),0);

    char idprompt[] = "Enter student id:";
    send(sd,&idprompt,strlen(idprompt),0);
    
    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    int offset = (id-1)*(sizeof(struct studentInfo));
    struct studentInfo info; 
    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct studentInfo));

    char tmp[10*sizeof(struct studentInfo)];
    sprintf(tmp,"\nStudent Id : %d \nname: %s\nage: %d\nemail: %s\naddress: %s\n",info.ID,info.name,info.age,info.email,info.address);
    
    // printf("%d\n",strlen(tmp));
    // printf("%s",tmp);
    
    char studentinfo[strlen(tmp)];
    memcpy(&studentinfo,&tmp,strlen(tmp));
    send(sd,&tmp,sizeof(tmp),0);

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}

void modifyStudentDetails(int sd){
    int file = open("studentinfo.txt",O_RDWR | O_CREAT,0744);
    char value ='3';
    send(sd,&value,sizeof(value),0);

    char idprompt[] = "Enter student id:";
    send(sd,&idprompt,strlen(idprompt),0);
    
    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    int offset = (id-1)*(sizeof(struct studentInfo));
    struct studentInfo info; 
    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct studentInfo));
    printf("ID =%d\n",info.ID);
    printf("name = %s\n",info.name);
    printf("password = %s\n",info.password);
    printf("age =%d\n",info.age);
    printf("email =%s\n",info.email);
    printf("add =%s\n",info.address);
    char field[] ="Enter field to change";
    send(sd,&field,strlen(field),0);
    char fieldvalue[20];
    recv(sd,&fieldvalue,sizeof(fieldvalue),0);
    printf("field = %s \n",fieldvalue);
    char valstr[] = "Enter new value";
    send(sd,&valstr,strlen(valstr),0);
    char newvalue[50];
    int length = recv(sd,&newvalue,sizeof(newvalue),0);
    printf("new value = %s \n ",newvalue);
    if(strcmp(fieldvalue,"age")==0){
        info.age = atoi(newvalue);
    }else if(strcmp(fieldvalue,"name")==0){
        memcpy(&info.name,&newvalue,strlen(newvalue));
    }else if(strcmp(fieldvalue,"email")==0){
        memcpy(&info.email,&newvalue,strlen(newvalue));
    }else if(strcmp(fieldvalue,"address")==0){
        memcpy(&info.address,&newvalue,strlen(newvalue));
    }
    printf("after change");
    printf("ID =%d\n",info.ID);
    printf("name = %s\n",info.name);
    printf("active = %d",info.active);
    printf("password = %s\n",info.password);
    printf("age =%d\n",info.age);
    printf("email =%s\n",info.email);
    printf("add =%s\n",info.address);
    seekinfo = lseek(file,offset,SEEK_SET);
    int datawrite = write(file,&info,sizeof(struct studentInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}

void activeStudent(int sd){
    int file = open("studentinfo.txt",O_RDWR | O_CREAT,0744);
    char value ='1';
    send(sd,&value,sizeof(value),0);

    char idprompt[] = "Enter student id:";
    send(sd,&idprompt,strlen(idprompt),0);
    
    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    int offset = (id-1)*(sizeof(struct studentInfo));
    struct studentInfo info; 
    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct studentInfo));

    info.active = true;
    seekinfo = lseek(file,offset,SEEK_SET);
    int datawrite = write(file,&info,sizeof(struct studentInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}


void blockStudent(int sd){
    int file = open("studentinfo.txt",O_RDWR | O_CREAT,0744);
    char value ='1';
    send(sd,&value,sizeof(value),0);

    char idprompt[] = "Enter student id:";
    send(sd,&idprompt,strlen(idprompt),0);
    
    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    int offset = (id-1)*(sizeof(struct studentInfo));
    struct studentInfo info; 
    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct studentInfo));

    info.active = false;
    seekinfo = lseek(file,offset,SEEK_SET);
    int datawrite = write(file,&info,sizeof(struct studentInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}

void addFaculty(int sd){
    int file = open("facultyinfo.txt",O_WRONLY | O_CREAT,0744);
    struct facultyInfo finfo;
    memset(&finfo,0,sizeof(finfo));
    char buffer[60];

    char value ='4';
    send(sd,&value,sizeof(value),0);        //send total length of questions

    finfo.ID =1;
    strcpy(finfo.password,"dummy");
    char msg1[] = "Enter Faculty Name:";
    send(sd,&msg1,strlen(msg1),0);
    recv(sd,&buffer,sizeof(buffer),0);
    strcpy(finfo.name,buffer);
    memset(&buffer,0,sizeof(buffer));

    char msg2[] = "Enter Faculty department:";
    send(sd,&msg2,strlen(msg2),0);
    recv(sd,&buffer,sizeof(buffer),0);
    strcpy(finfo.department,buffer);
    memset(&buffer,0,sizeof(buffer));
    
    char msg3[] ="Enter Faculty Email:";
    send(sd,&msg3,strlen(msg3),0);
    recv(sd,&buffer,sizeof(buffer),0);
    strcpy(finfo.email,buffer);
    memset(&buffer,0,sizeof(buffer));

    char msg4[] ="Enter Faculty designation:";
    send(sd,&msg4,strlen(msg4),0);
    recv(sd,&buffer,sizeof(buffer),0);
    strcpy(finfo.designation,buffer);
    //memset(buffer, '\0', sizeof(buffer));
    //bzero(buffer,sizeof(buffer));
    
    lseek(file,0,SEEK_END);
    write(file,&finfo,sizeof(struct studentInfo));
    printf("ID =%d\n",finfo.ID);
    printf("name = %s\n",finfo.name);
    printf("password = %s\n",finfo.password);
    printf("department =%s\n",finfo.department);
    printf("email =%s\n",finfo.email);
    printf("designaton =%s\n",finfo.designation);

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
	}
}


void viewFacultyDetails(int sd){

}


void adminFunctions(int sd){
    char str[10];
    char adminMenu[] = "\n-----Welcome to Admin Menu-----\n"
                "1. Add Student\n"
                "2. View Student details\n"
                "3. Add Faculty\n"
                "4. View faculty details\n"
                "5. Activate Student\n"
                "6. Block student\n"
                "7. Update Student details\n"
                "8. Update Faculty details\n"
                "0. Exit\n";
    
    send(sd,adminMenu,strlen(adminMenu),0);
    recv(sd,&str,sizeof(str),0);

    int adchoice = atoi(str);
    //printf("choice of admin menu : %d",adchoice);

    switch (adchoice)
    {
        case 1:
            addStudent(sd);
            break;
        case 2:
            viewStudentDetails(sd);
            break;
        case 3:
            modifyStudentDetails(sd);
            break;
        case 4:
            viewAllStudentDetails(sd);
            break;

        default:
            break;
    }
}
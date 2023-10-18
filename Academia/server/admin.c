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


int getId(){
    int file = open("studentinfo.txt",O_RDONLY | O_CREAT,0744);
    int len = sizeof(struct studentInfo);
    struct studentInfo info; 
    memset(&info,0,sizeof(info));
    int seekinfo = lseek(file,-len,SEEK_END);
    int dataread = read(file,&info,sizeof(struct studentInfo));

    return info.ID;
}

int getfacultyId(){
    int file = open("facultyinfo.txt",O_RDONLY | O_CREAT,0744);
    int len = sizeof(struct facultyInfo);
    struct facultyInfo info; 
    memset(&info,0,sizeof(info));
    int seekinfo = lseek(file,-len,SEEK_END);
    int dataread = read(file,&info,sizeof(struct facultyInfo));

    return info.ID;
}

void addStudent(int sd){
    int file = open("studentinfo.txt",O_WRONLY | O_CREAT,0744);
    struct studentInfo sinfo;
    memset(&sinfo,0,sizeof(sinfo));
    char buffer[60];
    memset(&buffer,0,sizeof(buffer));

    sinfo.ID =getId()+1;
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
    
    lseek(file,0,SEEK_END);
    write(file,&sinfo,sizeof(struct studentInfo));
    printf("ID =%d\n",sinfo.ID);
    printf("name = %s\n",sinfo.name);
    printf("active = %d\n",sinfo.active);
    printf("password = %s\n",sinfo.password);
    printf("age =%d\n",sinfo.age);
    printf("email =%s\n",sinfo.email);
    printf("add =%s\n",sinfo.address);

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
	}
}



// void viewAllStudentDetails(int sd){


//     int file = open("studentinfo.txt",O_RDONLY | O_CREAT,0744);
//     // struct studentInfo stuinfo;
//     // int seekinfo = lseek(file,offset,SEEK_SET);
//     // int dataRead = read(file,&stuinfo,sizeof(struct studentInfo));
    
//     // printf("details are\n");

//     // printf("ID = %d\n",stuinfo.ID);
//     // printf("name = %s\n",stuinfo.name);
//     // printf("age =%d\n",stuinfo.age);
//     // printf("email =%s\n",stuinfo.email);
//     // printf("add =%s\n",stuinfo.address);


//     int offset =0;
//     int len = sizeof(struct studentInfo);
//     while(1){
// 		struct studentInfo info; 
// 		int seekinfo = lseek(file,offset,SEEK_SET);
// 		int dataread = read(file,&info,len);
// 		if(dataread == 0){
// 			break;
// 		}
// 		printf("Student Id : %d \n",info.ID);
// 		printf("name: %s\n",info.name);
//         printf("age: %d\n",info.age);
//         printf("email: %s\n",info.email);
//         printf("address: %s\n",info.address);
// 		offset+=len;
// 	}

//     int fileclose = close(file);
//     if(fileclose == -1){
// 		printf("Error closing file");
//     }
    
// }

void viewStudentDetails(int sd){
    int file = open("studentinfo.txt",O_RDONLY | O_CREAT,0744);

    char idprompt[] = "Enter student id:";
    send(sd,&idprompt,strlen(idprompt),0);
    
    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    int offset = (id-1)*(sizeof(struct studentInfo));
    struct studentInfo info; 
    memset(&info,0,sizeof(info));
    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct studentInfo));

    char tmp[3*sizeof(struct studentInfo)];
    memset(tmp,0,sizeof(tmp));
    sprintf(tmp,"Student Id : %d \nname: %s\nage: %d\nemail: %s\naddress: %s\nEnter any character to continue",info.ID,info.name,info.age,info.email,info.address);
    
    send(sd,&tmp,strlen(tmp),0);
    recv(sd,&idstr,sizeof(idstr),0);
    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}

void modifyStudentDetails(int sd){
    int file = open("studentinfo.txt",O_RDWR | O_CREAT,0744);
   
    char idprompt[] = "Enter student id:";
    send(sd,&idprompt,strlen(idprompt),0);
    
    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    int offset = (id-1)*(sizeof(struct studentInfo));
    struct studentInfo info; 
    memset(&info,0,sizeof(info));

    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct studentInfo));

    char field[] ="Enter field to change";
    send(sd,&field,strlen(field),0);

    char fieldvalue[20];
    memset(&fieldvalue,0,sizeof(fieldvalue));
    recv(sd,&fieldvalue,sizeof(fieldvalue),0);

    char valstr[] = "Enter new value";
    send(sd,&valstr,strlen(valstr),0);

    char newvalue[50];
    memset(&newvalue,0,sizeof(newvalue));
    int length = recv(sd,&newvalue,sizeof(newvalue),0);
    
    if(strcmp(fieldvalue,"age")==0){
        info.age = atoi(newvalue);
    }else if(strcmp(fieldvalue,"name")==0){
        memset(&info.name,0,sizeof(info.name));
        memcpy(&info.name,&newvalue,strlen(newvalue));
    }else if(strcmp(fieldvalue,"email")==0){
        memset(&info.email,0,sizeof(info.email));
        memcpy(&info.email,&newvalue,strlen(newvalue));
    }else if(strcmp(fieldvalue,"address")==0){
        memset(&info.address,0,sizeof(info.address));
        memcpy(&info.address,&newvalue,strlen(newvalue));
    }
   
    lseek(file,offset,SEEK_SET);
    write(file,&info,sizeof(struct studentInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}

void activateOrBlockStudent(int sd,bool activate){
    int file = open("studentinfo.txt",O_RDWR | O_CREAT,0744);
    // char value ='1';
    // send(sd,&value,sizeof(value),0);

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

    info.active = activate;
    seekinfo = lseek(file,offset,SEEK_SET);
    int datawrite = write(file,&info,sizeof(struct studentInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}


// void blockStudent(int sd){
//     int file = open("studentinfo.txt",O_RDWR | O_CREAT,0744);
//     char value ='1';
//     send(sd,&value,sizeof(value),0);

//     char idprompt[] = "Enter student id:";
//     send(sd,&idprompt,strlen(idprompt),0);
    
//     char idstr[10];
//     int id;
//     recv(sd,&idstr,sizeof(idstr),0);
//     id = atoi(idstr);

//     int offset = (id-1)*(sizeof(struct studentInfo));
//     struct studentInfo info; 
//     int seekinfo = lseek(file,offset,SEEK_SET);
//     int dataread = read(file,&info,sizeof(struct studentInfo));

//     info.active = false;
//     seekinfo = lseek(file,offset,SEEK_SET);
//     int datawrite = write(file,&info,sizeof(struct studentInfo));

//     int fileclose = close(file);
//     if(fileclose == -1){
// 		printf("Error closing file");
//     }
// }

void addFaculty(int sd){
    int file = open("facultyinfo.txt",O_WRONLY | O_CREAT,0744);
    struct facultyInfo finfo;
    memset(&finfo,0,sizeof(finfo));
    char buffer[60];
    memset(&buffer,0,sizeof(buffer));

    finfo.ID =getfacultyId()+1;
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
    
    lseek(file,0,SEEK_END);
    write(file,&finfo,sizeof(struct facultyInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
	}
}


void viewFacultyDetails(int sd){
    int file = open("facultyinfo.txt",O_RDONLY | O_CREAT,0744);
    // char value ='2';
    // send(sd,&value,sizeof(value),0);

    char idprompt[] = "Enter faculty id:";
    send(sd,&idprompt,strlen(idprompt),0);
    
    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    int offset = (id-1)*(sizeof(struct facultyInfo));
    struct facultyInfo info; 
    memset(&info,0,sizeof(info));
    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct facultyInfo));

    char tmp[3*sizeof(struct facultyInfo)];
    sprintf(tmp,"Faculty Id : %d \nName: %s\nEmail: %s\nDesignation: %s\nDepartment: %s\nEnter any character to continue",info.ID,info.name,info.email,info.designation,info.department);
    
    send(sd,&tmp,strlen(tmp),0);
    recv(sd,&idstr,sizeof(idstr),0);
    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}


void modifyFacultyDetails(int sd){
    int file = open("facultyinfo.txt",O_RDWR | O_CREAT,0744);
    // char value ='3';
    // send(sd,&value,sizeof(value),0);

    char idprompt[] = "Enter faculty id:";
    send(sd,&idprompt,strlen(idprompt),0);
    
    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    int offset = (id-1)*(sizeof(struct facultyInfo));
    struct facultyInfo info;
    memset(&info,0,sizeof(info));
    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct facultyInfo));
    // printf("ID =%d\n",info.ID);
    // printf("name = %s\n",info.name);
    // printf("password = %s\n",info.password);
    // printf("department =%s\n",info.department);
    // printf("email =%s\n",info.email);
    // printf("designation =%s\n",info.designation);
    char field[] ="Enter field to change";
    send(sd,&field,strlen(field),0);
    char fieldvalue[20];
    recv(sd,&fieldvalue,sizeof(fieldvalue),0);
    //printf("field = %s \n",fieldvalue);
    char valstr[] = "Enter new value";
    send(sd,&valstr,strlen(valstr),0);
    char newvalue[50];
    int length = recv(sd,&newvalue,sizeof(newvalue),0);
    printf("new value = %s \n ",newvalue);
    if(strcmp(fieldvalue,"designation")==0){
        memset(&info.designation,0,sizeof(info.designation));
        memcpy(&info.designation,&newvalue,strlen(newvalue));
    }else if(strcmp(fieldvalue,"name")==0){
        memset(&info.name,0,sizeof(info.name));
        memcpy(&info.name,&newvalue,strlen(newvalue));
    }else if(strcmp(fieldvalue,"email")==0){
        memset(&info.email,0,sizeof(info.email));
        memcpy(&info.email,&newvalue,strlen(newvalue));
    }else if(strcmp(fieldvalue,"department")==0){
        memset(&info.department,0,sizeof(info.department));
        memcpy(&info.department,&newvalue,strlen(newvalue));
    }
    // printf("after change\n");
    // printf("ID =%d\n",info.ID);
    // printf("name = %s\n",info.name);
    // printf("password = %s\n",info.password);
    // printf("department =%s\n",info.department);
    // printf("email =%s\n",info.email);
    // printf("designation =%s\n",info.designation);
    seekinfo = lseek(file,offset,SEEK_SET);
    int datawrite = write(file,&info,sizeof(struct facultyInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}

void adminFunctions(int sd){

    while (1){
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
                    "9. Exit\n";
        
        send(sd,adminMenu,strlen(adminMenu),0);
        recv(sd,&str,sizeof(str),0);

        int adchoice = atoi(str);

        switch (adchoice)
        {
            case 1:
                addStudent(sd);
                break;
            case 2:
                viewStudentDetails(sd);
                break;
            case 3:
                addFaculty(sd);
                break;
            case 4:
                viewFacultyDetails(sd);
                break;
            case 5:
                activateOrBlockStudent(sd,true);
                break;
            case 6:
                activateOrBlockStudent(sd,false);
                break;
            case 7:
                modifyStudentDetails(sd);
                break;
            case 8:
                modifyFacultyDetails(sd);
                break;
            default:
                break;
        }
    }
}
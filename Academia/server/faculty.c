#include "../headers.h"



int getcourseId(){
    int file = open("courseinfo.txt",O_RDONLY | O_CREAT,0744);
    int len = sizeof(struct courseInfo);
    struct courseInfo info; 
    memset(&info,0,sizeof(info));
    int seekinfo = lseek(file,-len,SEEK_END);
    int dataread = read(file,&info,sizeof(struct courseInfo));

    printf("id = %d",info.Id);

    return info.Id;
}

void addCourse(int sd,int facid){
    int file = open("courseinfo.txt",O_WRONLY | O_CREAT,0744);

    struct courseInfo cinfo;
    memset(&cinfo,0,sizeof(cinfo));
    char buffer[60];
    memset(&buffer,0,sizeof(buffer));

    // char value ='5';
    // send(sd,&value,sizeof(value),0);        //send total length of questions
    cinfo.facultyId = facid;
    cinfo.Id =getcourseId()+1;
    cinfo.deleted = false;
    char msg1[50];
    strcpy(msg1,"Enter Course Name:");
    send(sd,&msg1,strlen(msg1),0);
    recv(sd,&buffer,sizeof(buffer),0);
    strcpy(cinfo.courseName,buffer);
    memset(&buffer,0,sizeof(buffer));
    memset(&msg1,0,sizeof(msg1));

    // strcpy(msg1,"Enter Faculty ID");
    // send(sd,&msg1,strlen(msg1),0);
    // recv(sd,&buffer,sizeof(buffer),0);
    // cinfo.facultyId = atoi(buffer);
    // memset(&buffer,0,sizeof(buffer));
    // memset(&msg1,0,sizeof(msg1));
    
    strcpy(msg1,"Enter Faculty name");
    send(sd,&msg1,strlen(msg1),0);
    recv(sd,&buffer,sizeof(buffer),0);
    strcpy(cinfo.facultyName,buffer);
    memset(&buffer,0,sizeof(buffer));
    memset(&msg1,0,sizeof(msg1));

    strcpy(msg1,"Enter total seats for the course");
    send(sd,&msg1,strlen(msg1),0);
    recv(sd,&buffer,sizeof(buffer),0);
    cinfo.totalSeats = atoi(buffer);
    cinfo.remSeats = atoi(buffer);
    memset(&buffer,0,sizeof(buffer));
    memset(&msg1,0,sizeof(msg1));

    strcpy(msg1,"Enter course code");
    send(sd,&msg1,strlen(msg1),0);
    recv(sd,&buffer,sizeof(buffer),0);
    strcpy(cinfo.courseCode,buffer);
    memset(&buffer,0,sizeof(buffer));
    memset(&msg1,0,sizeof(msg1));

    lseek(file,0,SEEK_END);
    write(file,&cinfo,sizeof(struct courseInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
	}
}

int findCourseByFaculty(int sd,int facultyId){

    int file = open("courseinfo.txt",O_RDONLY | O_CREAT,0744);
    
    int offset =0;
    int len = sizeof(struct courseInfo);
    char tmp[3*len];
    char str[50*len];
    char *variable;
    variable = str;
    memset(&tmp,0,sizeof(tmp));
    memset(&str,0,sizeof(str));
    while(1){
        struct courseInfo info; 
        int seekinfo = lseek(file,offset,SEEK_SET);
        int dataread = read(file,&info,len);
        if(dataread==0){
            break;
        }
        printf("deleted value %s %d\n",info.courseName,info.deleted);

        if(info.facultyId ==facultyId){
            if(info.deleted == 0){
                sprintf(tmp,"\nCourse Id: %d \nCourse Name: %s\nCourse code: %s\nTotal seats: %d\nRemaining seats: %d",info.Id,info.courseName,info.courseCode,info.totalSeats,info.remSeats);
                strcat(variable,tmp);
                //printf("tmp: %s\n",tmp);
            }
        }
        offset+=len;
    }
    //printf("str = %s\n",str);
    strcat(str,"\nEnter Id of the course to remove\n");
    send(sd,&str,strlen(str),0);
    char cId[10];
    recv(sd,&cId,sizeof(cId),0);
    int fileclose = close(file);
    if(fileclose == -1){
        printf("Error closing file");
    }
    return atoi(cId);
}


void viewOfferedCourses(int sd,int facultyId){

    int file = open("courseinfo.txt",O_RDONLY | O_CREAT,0744);
    
    int offset =0;
    int len = sizeof(struct courseInfo);
    char tmp[3*len];
    char str[50*len];
    char *variable;
    variable = str;
    memset(&tmp,0,sizeof(tmp));
    memset(&str,0,sizeof(str));
    while(1){
        struct courseInfo info; 
        int seekinfo = lseek(file,offset,SEEK_SET);
        int dataread = read(file,&info,len);
        if(dataread==0){
            break;
        }
        //printf("deleted value %s %d\n",info.courseName,info.deleted);

        if(info.facultyId ==facultyId){
            if(info.deleted == 0){
                sprintf(tmp,"\nCourse Id: %d \nCourse Name: %s\nCourse code: %s\nTotal seats: %d\nRemaining seats: %d",info.Id,info.courseName,info.courseCode,info.totalSeats,info.remSeats);
                strcat(variable,tmp);
                //printf("tmp: %s\n",tmp);
            }
        }
        offset+=len;
    }
    send(sd,&str,strlen(str),0);
    recv(sd,&str,strlen(str),0);
    int fileclose = close(file);
    if(fileclose == -1){
        printf("Error closing file");
    }
}


// void viewAllCourses(){
//     int file = open("courseinfo.txt",O_RDONLY | O_CREAT,0744);

//     int offset =0;
//     int len = sizeof(struct courseInfo);
//     while(1){
// 		struct courseInfo info; 
// 		int seekinfo = lseek(file,offset,SEEK_SET);
// 		int dataread = read(file,&info,len);
// 		if(dataread == 0){
// 			break;
// 		}
// 		printf("course Id : %d \n",info.Id);
// 		printf("name: %s\n",info.courseName);
//         printf("seats: %d\n",info.totalSeats);
//         printf("faculty name: %s\n",info.facultyName);
//         //printf("address: %s\n",info.address);
// 		offset+=len;
// 	}

//     int fileclose = close(file);
//     if(fileclose == -1){
// 		printf("Error closing file");
//     }
// }

void removeCourse(int sd,int courseId){
    int file = open("courseinfo.txt",O_RDWR | O_CREAT,0744);

    int len = sizeof(struct courseInfo);
    int offset = (courseId-1)*len;
    struct courseInfo info; 
    memset(&info,0,sizeof(info));
    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,len);
    
    // printf("\n\n Inside remove course");
    // printf("course Id : %d \n",info.Id);
    // printf("name: %s\n",info.courseName);
    // printf("seats: %d\n",info.totalSeats);
    // printf("faculty name: %s\n",info.facultyName);
    // printf("deleted before: %d\n",info.deleted);
    // printf("address: %s\n",info.address);
    info.deleted = true;
    // printf("deleted after: %d\n",info.deleted);
    lseek(file,offset,SEEK_SET);
    write(file,&info,len);


    int fileclose = close(file);
    if(fileclose == -1){
        printf("Error closing file");
    }
}

// void viewAllCourses(){
//     int file = open("courseinfo.txt",O_RDONLY | O_CREAT,0744);
//     int offset =0;
//     int len = sizeof(struct courseInfo);
//     printf("Entering View course:");
//     while(1){
// 		struct courseInfo info; 
// 		int seekinfo = lseek(file,offset,SEEK_SET);
// 		int dataread = read(file,&info,len);
// 		if(dataread == 0){
// 			break;
// 		}
// 		printf("course Id : %d \n",info.Id);
// 		printf("name: %s\n",info.courseName);
//         printf("seats: %d\n",info.totalSeats);
//         printf("faculty name: %s\n",info.facultyName);
//         printf("deleted %d\n",info.deleted);
// 		offset+=len;
// 	    }
//     int fileclose = close(file);
//     if(fileclose == -1){
// 		printf("Error closing file");
//     }
// }

void updateCourse(int sd,int facid){

    int file = open("courseinfo.txt",O_RDWR | O_CREAT,0744);
   
    char idprompt[] = "Enter course id:";
    send(sd,&idprompt,strlen(idprompt),0);
    
    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    int offset = (id-1)*(sizeof(struct courseInfo));
    struct courseInfo info; 
    memset(&info,0,sizeof(info));

    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct courseInfo));

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
    
    if(strcmp(fieldvalue,"coursename")==0){
        memset(&info.courseName,0,sizeof(info.courseName));
        memcpy(&info.courseName,&newvalue,strlen(newvalue));
    }else if(strcmp(fieldvalue,"facultyname")==0){
        memset(&info.facultyName,0,sizeof(info.facultyName));
        memcpy(&info.facultyName,&newvalue,strlen(newvalue));
    }else if(strcmp(fieldvalue,"totalseats")==0){
        memset(&info.totalSeats,0,sizeof(info.totalSeats)); 
        info.totalSeats = atoi(newvalue);

    }else if(strcmp(fieldvalue,"coursecode")==0){
        memset(&info.courseCode,0,sizeof(info.courseCode));
        memcpy(&info.courseCode,&newvalue,strlen(newvalue));
    }
   
    lseek(file,offset,SEEK_SET);
    write(file,&info,sizeof(struct courseInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}


void changeFacultyPassword(int sd,int facid){
    int file = open("facultyinfo.txt",O_RDWR | O_CREAT,0744);
    int offset = (facid-1)*(sizeof(struct facultyInfo));
    
    struct facultyInfo info; 
    memset(&info,0,sizeof(info));

    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct facultyInfo));

    char valstr[] = "Enter new password";
    send(sd,&valstr,strlen(valstr),0);
    char newvalue[50];
    recv(sd,&newvalue,sizeof(newvalue),0);
    strcpy(info.password,newvalue);

    lseek(file,offset,SEEK_SET);
    write(file,&info,sizeof(struct facultyInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}

void facultyFunctions(int sd,int facid){

    while (1){
        char str[10];
        int cId;
        char facultyMenu[] = "\n-----Welcome to Faculty Menu-----\n"
                    "1. View offered courses\n"
                    "2. Add new Course\n"
                    "3. Remove offered Course\n"
                    "4. Update course details\n"
                    "5. Password Change\n"
                    "9. Exit\n";
        
        send(sd,facultyMenu,strlen(facultyMenu),0);
        recv(sd,&str,sizeof(str),0);

        int ftychoice = atoi(str);

        switch (ftychoice)
        {
            case 1:
                viewOfferedCourses(sd,facid);
                break;
            case 2:
                addCourse(sd,facid);
                break;
            case 3:
                cId = findCourseByFaculty(sd,facid);
                removeCourse(sd,cId);
                break;
            case 4:
                updateCourse(sd,facid);
                break;
            case 5:
                changeFacultyPassword(sd,facid);
                break;
            case 6:
                // viewAllCourses();
                break;
            default:
                break;
        }
    }

}
#include "../headers.h"

struct courseInfo{
    int Id;
    char courseName[30];
    int facultyId;
    char facultyName[30];
    int totalSeats;
    int remSeats;
    char courseCode[10];
    bool deleted;
};

struct enrollDetails{
    int courseId;
    int studentId;
    bool deleted;
};

int printcourse(int sd){
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
        if(info.deleted == 0){
            sprintf(tmp,"\nCourse Id: %d \nCourse Name: %s\nCourse code: %s\nTotal seats: %d\nRemaining seats: %d",
                info.Id,info.courseName,info.courseCode,info.totalSeats,info.remSeats);
            strcat(variable,tmp);
            // printf("tmp: %s\n",tmp);
        }

        offset+=len;
    }
    strcat(variable,"\nEnter courseId of the course to enroll");
    send(sd,&str,strlen(str),0);
    char cId[10];
    recv(sd,&cId,sizeof(cId),0);
    int fileclose = close(file);
    printf("atoi %d\n",atoi(cId));
    printf("str = %s\n",str);
    if(fileclose == -1){
        printf("Error closing file");
    }
    return atoi(cId);
}

bool decrementSeats(int courseId){
    int file = open("courseinfo.txt",O_RDWR | O_CREAT,0744);

    bool ans;
    int len = sizeof(struct courseInfo);
    int offset = (courseId-1)*len;
    struct courseInfo info; 
    memset(&info,0,sizeof(info));
    lseek(file,offset,SEEK_SET);
    read(file,&info,len);

    if(info.remSeats >0){
        info.remSeats--;
        ans = true;
        lseek(file,offset,SEEK_SET);
        write(file,&info,len);
    }else{
        ans = false;
    }
    int fileclose = close(file);
    if(fileclose == -1){
        printf("Error closing file");
    }
    return ans;

}

bool incrementSeats(int courseId){
    int file = open("courseinfo.txt",O_RDWR | O_CREAT,0744);

    bool ans;
    int len = sizeof(struct courseInfo);
    int offset = (courseId-1)*len;
    struct courseInfo info; 
    memset(&info,0,sizeof(info));
    lseek(file,offset,SEEK_SET);
    read(file,&info,len);

    if(info.remSeats <info.totalSeats){
        info.remSeats++;
        ans = true;
        lseek(file,offset,SEEK_SET);
        write(file,&info,len);
    }else{
        ans = false;
    }
    int fileclose = close(file);
    if(fileclose == -1){
        printf("Error closing file");
    }
    return ans;

}

void enroll(int sd,int studentId){
    int file = open("enrollments.txt",O_RDWR | O_CREAT,0744);

    char idprompt[] = "Enter course id to enroll";
    send(sd,&idprompt,strlen(idprompt),0);

    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    struct enrollDetails enrolldetails;
    memset(&enrolldetails,0,sizeof(struct enrollDetails));

    enrolldetails.deleted = false;
    enrolldetails.courseId = id;
    enrolldetails.studentId = studentId;

    bool answer = decrementSeats(id);

    char str[100];
    memset(&str,0,sizeof(str));
    if(answer){
        lseek(file,0,SEEK_END);
        write(file,&enrolldetails,sizeof(struct enrollDetails));
        strcpy(str,"\nCourse enroll successfull.\nEnter any character to continue");
    }else{
        strcpy(str,"\nError enrolling in course.\nEnter any character to continue");
    }

    send(sd,&str,strlen(str),0);
    recv(sd,&str,strlen(str),0);


    int fileclose = close(file);
    if(fileclose == -1){
        printf("Error closing file");
    }
}

void deenroll(int sd,int stuid){
    int file = open("enrollments.txt",O_RDWR | O_CREAT,0744);

    char idprompt[] = "Enter course id to deenroll";
    send(sd,&idprompt,strlen(idprompt),0);

    char idstr[10];
    int id;
    recv(sd,&idstr,sizeof(idstr),0);
    id = atoi(idstr);

    struct enrollDetails enrolldetails;
    memset(&enrolldetails,0,sizeof(struct enrollDetails));
    int offset =0;
    int len = sizeof(struct enrollDetails);
    bool answer= false;
    while (1)
    {
		lseek(file,offset,SEEK_SET);
		read(file,&enrolldetails,len);
        printf("%d\n",enrolldetails.deleted);
        printf("%d\n",enrolldetails.courseId);

        if(enrolldetails.deleted == 0 && stuid == enrolldetails.studentId && enrolldetails.courseId == id){
            enrolldetails.deleted = true;

            answer = incrementSeats(id);
            break;
        }
        offset+=len;
    }

    char str[100];
    memset(&str,0,sizeof(str));
    if(answer){
        lseek(file,offset,SEEK_SET);
        write(file,&enrolldetails,sizeof(struct enrollDetails));
        strcpy(str,"\nCourse deenroll successfull.\nEnter any character to continue");
    }else{
        strcpy(str,"\nError deenrolling in course.\nEnter any character to continue");
    }

    send(sd,&str,strlen(str),0);
    recv(sd,&str,strlen(str),0);


    int fileclose = close(file);
    if(fileclose == -1){
        printf("Error closing file");
    }
}



void viewEnrollments(int sd,int studentId){
    int file = open("enrollments.txt",O_RDWR | O_CREAT,0744);
    int offset =0;
    int len = sizeof(struct enrollDetails);
    int cfile = open("courseinfo.txt",O_RDONLY | O_CREAT,0744);
    int coffset =0;
    int clen = sizeof(struct courseInfo);
    char list[300];
    memset(&list,0,sizeof(list));
    char tmp[len*4];
	while(1){
		struct enrollDetails details; 
        memset(&details,0,sizeof(details));
		lseek(file,offset,SEEK_SET);
		int dataread = read(file,&details,len);
		if(dataread == 0){
			break;
		}
        if(details.studentId == studentId && details.deleted ==0){
            //find course details
            struct courseInfo info; 
            memset(&info,0,sizeof(info));
            coffset = (details.courseId-1)*(sizeof(struct courseInfo));
            lseek(cfile,coffset,SEEK_SET);
            read(cfile,&info,clen);
            sprintf(tmp,"Course ID: %d\t Course name:%s\t Course code: %s\n",details.courseId,info.courseName,info.courseCode);
        }
        strcat(list,tmp);
        memset(&tmp,0,sizeof(tmp));
		offset+=len;
	}
    strcat(list,"\nEnter any character to continue\n");
    send(sd,&list,strlen(list),0);
    recv(sd,&list,strlen(list),0);
    close(cfile);
    int fileclose = close(file);
    if(fileclose == -1){
        printf("Error closing file");
    }
}



void viewAllCourses(int sd){
    int file = open("courseinfo.txt",O_RDONLY | O_CREAT,0744);
    int offset =0;
    int len = sizeof(struct courseInfo);
    char list[300];
    memset(&list,0,sizeof(list));
    char tmp[len*4];
    memset(&tmp,0,sizeof(tmp));
    while(1){
		struct courseInfo info;
        memset(&info,0,sizeof(info));
		int seekinfo = lseek(file,offset,SEEK_SET);
		int dataread = read(file,&info,len);
		if(dataread == 0){
			break;
		}
		// printf("course Id : %d \n",info.Id);
		// printf("name: %s\n",info.courseName);
        // printf("seats: %d\n",info.totalSeats);
        // printf("faculty name: %s\n",info.facultyName);
        if(info.deleted ==0){
            sprintf(tmp,"\nCourse Id: %d \nCourse Name: %s\nCourse code: %s\nTotal seats: %d\nRemaining seats: %d",info.Id,info.courseName,info.courseCode,info.totalSeats,info.remSeats);
            strcat(list,tmp);
        }
		offset+=len;
    }
    strcat(list,"\nEnter any character to continue\n");
    send(sd,&list,strlen(list),0);
    recv(sd,&list,strlen(list),0);
    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}

void changeStudentPassword(int sd,int stuid){
    int file = open("studentinfo.txt",O_RDWR | O_CREAT,0744);
    int offset = (stuid-1)*(sizeof(struct studentInfo));
    
    struct studentInfo info; 
    memset(&info,0,sizeof(info));
    
    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct studentInfo));
    
    char valstr[] = "Enter new password";
    send(sd,&valstr,strlen(valstr),0);
    char newvalue[50];
    recv(sd,&newvalue,sizeof(newvalue),0);
    strcpy(info.password,newvalue);
    lseek(file,offset,SEEK_SET);
    write(file,&info,sizeof(struct studentInfo));
    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
}

bool isActive(int id){
    int file = open("studentinfo.txt",O_RDWR | O_CREAT,0744);
    int offset = (id-1)*(sizeof(struct studentInfo));
    struct studentInfo info; 
    int seekinfo = lseek(file,offset,SEEK_SET);
    int dataread = read(file,&info,sizeof(struct studentInfo));

    int fileclose = close(file);
    if(fileclose == -1){
		printf("Error closing file");
    }
    if(info.active){
        return true;
    }else{
        return false;
    }
}

void studentFunctions(int sd,int stuid){

    while (1){
        char str[10];
        char studentMenu[] = "\n-----Welcome to Student Menu-----\n"
                    "1. View all courses\n"
                    "2. Enroll to new Course\n"
                    "3. Drop Course\n"
                    "4. View enrolled Courses\n"
                    "5. Password Change\n"
                    "9. Exit\n";
        
        send(sd,studentMenu,strlen(studentMenu),0);
        recv(sd,&str,sizeof(str),0);

        int stuchoice = atoi(str);

        switch (stuchoice)
        {
            case 1:
                viewAllCourses(sd);
                break;
            case 2:
                enroll(sd,stuid);
                break;
            case 3:
                deenroll(sd,stuid);
                break;
            case 4:
                viewEnrollments(sd,stuid);
                break;
            case 5:
                changeStudentPassword(sd,stuid);
                break;

            default:
                break;
        }
    }
}
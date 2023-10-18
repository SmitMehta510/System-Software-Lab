#include "../headers.h"
#include "admin.c"
#include "login.c"
#include "student.c"
#include "faculty.c"

#define MAX_PENDING 5

void tcpData(){

    int listensd;       // Listen socket descriptor
    int connectsd;      // Connecting socket descriptor
    int len;
    int processId;      //process ID of child process

    struct sockaddr_in sin;

    /*Creating new socket,AF_INET/PF_INET can be used interchangeably to
     indicate socket will be used for IPv4 communication.SOCK_STREAM is used for TCP connection, 
    0 is given as protocol value for TCP/IP protocol suite*/
    if ((listensd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
            perror("simplex-talk: socket");
            exit(1);
    }

    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(5432); 
    if ((bind(listensd, (struct sockaddr *)&sin, sizeof(sin))) < 0){
            perror("simplex-talk: bind");
            exit(1);
    }
    else{
            printf("Server bind done.\n");
    }

    listen(listensd, MAX_PENDING);
    char string[10];
    int choice = -1;

    while (1){
        if ((connectsd = accept(listensd, (struct sockaddr *)&sin, &len)) < 0) {
            perror("simplex-talk: accept\n");
            exit(1);
        }

        processId = fork();

        if(processId ==0){
            char buff[] = "----------Welcome to Academia ----------\n"
                        "Choose login type \n"
                        "1. Admin\t 2. Student\t 3. Faculty\n";
            int bytesSend = send(connectsd,&buff,sizeof(buff),0);
            int recvBytes = recv(connectsd,&string,sizeof(string),0);
            choice = atoi(string);
        
            char error[] ="Invalid credentials. Try again";
            char username[30],password[30];
            bzero(password,sizeof(password));
            bzero(username,sizeof(username));
            int Id;
            char msg[30];
            if(choice!=1){
                strcpy(msg,"Enter User Id");
                send(connectsd,&msg,strlen(msg),0);
                recv(connectsd,&username,sizeof(username),0);
                memset(&msg,0,sizeof(msg));

                strcpy(msg,"Enter Password");
                send(connectsd,&msg,strlen(msg),0);
                recv(connectsd,&password,sizeof(password),0);
                memset(&msg,0,sizeof(msg));

                Id = atoi(username);
            }
            char buffer[30];
            switch (choice)
            {
                case 1:
                    adminFunctions(connectsd);
                    break;
                case 2:
                    if(studentLogin(Id,password)){
                        studentFunctions(connectsd,Id);
                    }else{
                        send(connectsd,&error,strlen(error),0);
                    }
                    break;
                case 3:
                    if(facultyLogin(Id,password)){
                        facultyFunctions(connectsd,Id);
                    }else{
                        send(connectsd,&error,strlen(error),0);
                        shutdown(connectsd,SHUT_RDWR);
                        close(connectsd);
                    }
                    break;
                default:
                    exit(0);
                    break;
            }
        }
        close(connectsd);

    }
}





int main(int argc, char const *argv[])
{
    tcpData();

    //viewAllEnrollments();
    //studentFunctions(1,1);
    return 0;
}



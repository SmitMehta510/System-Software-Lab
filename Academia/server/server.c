#include "../headers.h"
#include "admin.c"
#include "login.c"

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
                        "1. Admin\t 2. Faculty\t 3. Student\n";
            int bytesSend = send(connectsd,&buff,sizeof(buff),0);
            int recvBytes = recv(connectsd,&string,sizeof(string),0);
            choice = atoi(string);
            //int wr = write(0,&choice,sizeof(choice));
            
            char buffer[100];
            // //login data
            // struct loginInfo linfo;
            // memset(&linfo,0,sizeof(linfo));
            
            // linfo.usertype = choice;
            // char msg[] = "Enter username :";
            // send(connectsd,&msg,sizeof(msg),0);
            // // int endbyte = recv(connectsd,&buffer,sizeof(buffer),0);
            // // memcpy(linfo.uname,buffer,endbyte);

            // bzero(buffer,sizeof(buffer));
            // strcpy(msg,"Enter password :");
            // send(connectsd,&msg,sizeof(msg),0);
            // // endbyte = recv(connectsd,&buffer,sizeof(buffer),0);
            // // memcpy(linfo.password,buffer,endbyte);

            // printf("uname = %s\n",linfo.uname);
            // printf("password = %s\n",linfo.password);
            

            // struct loginInfo info;
            // memset(&info,0,sizeof(struct loginInfo));
            // int file = open("logininfo.txt",O_RDONLY | O_CREAT,0744);

            // int dataread = read(file,&info,sizeof(struct loginInfo));


            // printf("choice: %d\n",info.usertype == linfo.usertype);
            // printf("%d \n",strcmp(info.uname,linfo.uname));
            // printf("%d \n",strcmp(info.password,linfo.password));

            // printf("%d\n",login(linfo.usertype,linfo.uname,linfo.password));
            switch (choice)
            {
                case 1:
                    adminFunctions(connectsd);
                    // viewAllStudentDetails(connectsd);
                    // viewStudentDetails(connectsd);
                    break;
                case 2:
                    break;
                case 3:
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
    //saveinfo();
    tcpData();
    return 0;
}



#include "../headers.h"

struct args
{
    char* ip;
    int port;
    char* name;
}ptr;


struct loginInfo
{
    int usertype;
    char uname[20];
    char password[20];
}linfo;

int senddata,recvdata;

void tcp(){
    struct sockaddr_in sin;
    int sd;
    struct hostent *hp;
    char *host;


    char buf[256];
    int len;

    host = ptr.ip;      //ptr.ip has the ip to which client is connecting to.
    hp = gethostbyname(host);
    if (!hp){
        fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
        exit(1);
    }

    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
    sin.sin_port = htons(ptr.port);     //host to network short

    if ((sd = socket(PF_INET, SOCK_STREAM, 0)) < 0){
        perror("simplex-talk: socket");
        exit(1);
    }else{
        printf("Client created socket.\n");
    }

        

    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin)) < 0){
        perror("simplex-talk: connect");
        close(sd);
        exit(1);
    }

    recvdata = recv(sd,&buf,sizeof(buf),0);

    int writedata = write(1,buf,recvdata);

    char choiceprompt[] ="Enter your choice : ";
    writedata = write(1,choiceprompt,sizeof(choiceprompt));

    int readchoice;
    int choice = read(0,&readchoice,sizeof(readchoice));

    senddata = send(sd,&readchoice,sizeof(readchoice),0);

    // linfo.usertype = choice;
    // char name[20],pass[20],tmp[20];
    // recvdata = recv(sd,&buf,sizeof(buf),0);        //receive uname prompt for login
    // writedata = write(1,buf,recvdata);
    // //read(0,&tmp,sizeof(tmp));
    // scanf("%[^\n]", tmp);
    // strcpy(linfo.uname,tmp);
    // // memcpy(name,tmp,strlen(tmp));
    // // senddata = send(sd,&name,sizeof(name),0);


    // bzero(tmp,sizeof(tmp));
    // recvdata = recv(sd,&buf,sizeof(buf),0);        //receive pass prompt for login
    // writedata = write(1,buf,recvdata);
    // //read(0,&tmp,sizeof(tmp));
    // scanf("%[^\n]", tmp);
    // strcpy(linfo.password,tmp);
    // // memcpy(pass,tmp,strlen(tmp));
    // // senddata = send(sd,&pass,sizeof(pass),0);
    // char outarr[sizeof(struct loginInfo)];
    // memcpy(&outarr,&linfo,sizeof(struct loginInfo));

    // senddata = send(sd,&outarr,sizeof(outarr),0);

    char menu[300],str[10],ques[200],buffer[100];

    recvdata = recv(sd,&menu,sizeof(menu),0);       //recieve options for the selected user
    writedata = write(1,menu,recvdata);

    writedata = write(1,choiceprompt,strlen(choiceprompt));     //ask for choice 

    int readdata = read(0,&str,sizeof(str));       //get the selected choice from the options
    senddata = send(sd,str,strlen(str),0);
    
    int tlength;        //total no of send and recv to be done given the choice selected
    char lenbuff[10];    
    bzero(ques,sizeof(ques));
    //while (1)
    //{
        recvdata = recv(sd,&lenbuff,sizeof(lenbuff),0);
        tlength = atoi(lenbuff);
        printf("tlength = %d",tlength);

        while(tlength-- >0){
            recvdata = recv(sd,&ques,sizeof(ques),0);
            printf("recvdata = %d\n",recvdata);
            printf("%s\n",ques);
            memset(&ques,0,sizeof(ques));

            scanf("%s",buffer);
            senddata = send(sd,&buffer,strlen(buffer),0);
            memset(&buffer,0,sizeof(buffer));
        }    
    //}
    
    close(sd);
    exit(0);
}

int main(int argc, char const *argv[])
{
    if(argc ==4){
        ptr.ip = argv[1];
        ptr.port = atoi(argv[2]);       //atoi to convet string to integer
        ptr.name = argv[3];

        tcp();
    }else{
        exit(0);
    }
    return 0;
}
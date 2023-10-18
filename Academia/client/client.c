#include "../headers.h"

struct args
{
    char* ip;
    int port;
    //char* name;
}ptr;




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

    

    char ques[300],buffer[100];
        int inputchoice;
        while(1){
            recvdata = recv(sd,&ques,sizeof(ques),0);
            printf("%s\n",ques);
            memset(&ques,0,sizeof(ques));

            scanf("%s",buffer);
            inputchoice = atoi(buffer);
            if(inputchoice == 9){
                shutdown(sd,SHUT_RDWR);
            }
            senddata = send(sd,&buffer,strlen(buffer),0);
            memset(&buffer,0,sizeof(buffer));
        }    
    
    
    close(sd);
    exit(0);
}

int main(int argc, char const *argv[])
{
    if(argc ==4){
        ptr.ip = argv[1];
        ptr.port = atoi(argv[2]);       //atoi to convet string to integer
        //ptr.name=argv[3];

        tcp();
    }else{
        exit(0);
    }
    return 0;
}
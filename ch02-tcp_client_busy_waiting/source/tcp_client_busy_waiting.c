#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void error_handling(char const* message);
int main(int argc,char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len=0,count=0;
    if(argc!=3){
        printf("Usage:%s <IP> <port>\n",argv[0]);
        exit(1);
    }
    sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock==-1){
        error_handling("socket() error!");
    }
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        error_handling("connect() error!");
    }
    for(count=0;count<3000;count++){
        printf("Wait time %d \n",count);
    }
    str_len=read(sock,message,sizeof(message)-1);
    if(str_len==-1){
        error_handling("read() error!");
    }
    printf("Message from server : %s \n",message);
    close(sock);
    return 0;
}
void error_handling(char const* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

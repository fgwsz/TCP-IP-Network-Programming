#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
void error_handling(char const* message);
int main(int argc,char* argv[]){
    int sd;
    FILE* fp;
    char buf[BUF_SIZE];
    int read_cnt;
    struct sockaddr_in serv_adr;
    if(argc!=3){
        printf("Usage:%s <IP> <port>\n",argv[0]);
        exit(1);
    }
    fp=fopen("receive.dat","wb");
    if(!fp){
        error_handling("fopen() error!");
    }
    sd=socket(PF_INET,SOCK_STREAM,0);
    if(sd==-1){
        error_handling("socket() error!");
    }
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));
    if(connect(sd,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1){
        error_handling("connect() error!");
    }
    while((read_cnt=read(sd,buf,BUF_SIZE))!=0){
        if(read_cnt==-1){
            error_handling("read() error!");
        }
        if(fwrite((void*)buf,1,read_cnt,fp)<read_cnt){
            error_handling("fwrite() error!");
        }
    }
    puts("Received file data");
    if(write(sd,"Thank you",10)==-1){
        error_handling("write() error!");
    }
    fclose(fp);
    close(sd);
    return 0;
}
void error_handling(char const* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char const* message);
int main(int argc,char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char msg_buf[BUF_SIZE];
    int str_len;
    if(argc!=3){
        printf("Usage:%s <IP> <port>\n",argv[0]);
        exit(1);
    }
    sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1){
        error_handling("socket() error!");
    }
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        error_handling("connect() error!");
    }else{
        puts("Connected..........");
    }
    memset(&msg_buf[0],0,BUF_SIZE);
    printf("Input message: ");
    //实现思路:
    //首先先通过传输一个文件路径名,来查询文件是否存在,如果存在就返回文件字节数,
    //否则返回-1
    //然后使用一个buf分块来接收文件内容
    str_len=string_length(msg_buf,BUF_SIZE);
    write(sock,msg_buf,str_len(msg_buf,BUF_SIZE));
    str_len=read(sock,message,sizeof(message)-1);
    if(str_length==-1){
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

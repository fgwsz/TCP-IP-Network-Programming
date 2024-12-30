#include<stdint.h>//uint32_t
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char const* message);
int main(int argc,char* argv[]){
    if(argc!=3){
        printf("Usage:%s <IP> <port>\n",argv[0]);
        exit(1);
    }
    int sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1){
        error_handling("socket() error!");
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        error_handling("connect() error!");
    }else{
        puts("Connected..........");
    }
    //传递一个字符串给服务器
    //协议:
    //[字符串长度(不包含末尾的'\0')][字符串]
    //|                            |
    //\       占用4个字节          /
    char string[]="Hello?";
    uint32_t string_length=(uint32_t)(sizeof(string)-1);
    char msg_buf[BUF_SIZE];
    memset(&msg_buf[0],0,sizeof(msg_buf));
    *((uint32_t*)&msg_buf[0])=string_length;
    memmove(&msg_buf[0+sizeof(uint32_t)],string,string_length);
    write(sock,msg_buf,sizeof(uint32_t)+string_length);

    uint32_t msg_len=read(sock,msg_buf,sizeof(msg_buf));
    if(msg_len==-1){
        error_handling("read() error!");
    }
    printf("Message from server : {length:%d,string:%s} \n",(uint32_t)msg_buf[0],&msg_buf[sizeof(uint32_t)]);
    close(sock);
    return 0;
}
void error_handling(char const* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

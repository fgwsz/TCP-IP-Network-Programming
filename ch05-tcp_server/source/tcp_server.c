#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char const* message);
int main(int argc,char* argv[]){
    if(argc!=2){
        printf("Usage:%s <port>\n",argv[0]);
        exit(1);
    }
    int serv_sock=socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock==-1){
        error_handling("socket() error!");
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        error_handling("bind() error!");
    }
    if(listen(serv_sock,5)==-1){
        error_handling("listen() error!");
    }
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size=sizeof(clnt_addr);
    int clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
    if(clnt_sock==-1){
        error_handling("accept() error!");
    }
    char msg_buf[BUF_SIZE];
    memset(&msg_buf[0],0,sizeof(msg_buf));
    uint32_t msg_len=read(clnt_sock,msg_buf,sizeof(msg_buf));
    if(msg_len==-1){
        error_handling("read() error!");
    }
    printf("Message from client : {length:%d,string:%s} \n",(uint32_t)msg_buf[0],&msg_buf[sizeof(uint32_t)]);

    //传递一个字符串给客户端
    //协议:
    //[字符串长度(不包含末尾的'\0')][字符串]
    //|                            |
    //\       占用4个字节          /
    char string[]="Hi,I'm Server.";
    uint32_t string_length=(uint32_t)(sizeof(string)-1);
    memset(&msg_buf[0],0,sizeof(msg_buf));
    *((uint32_t*)&msg_buf[0])=string_length;
    memmove(&msg_buf[0+sizeof(uint32_t)],string,string_length);
    write(clnt_sock,msg_buf,sizeof(uint32_t)+string_length);
    close(clnt_sock);
    close(serv_sock);
    return 0;
}
void error_handling(char const* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

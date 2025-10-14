#include<stdio.h>
//puts()
//putc()
//stdout
//printf()
#include<stdlib.h>
//atoi()
//exit()
#include<string.h>
//memset()
#include<sys/socket.h>
//socket()
//PF_INET
//SOCK_STREAM
//IPPROTO_TCP
//bind()
//socklen_t
//listen()
//accept()
#include<netinet/in.h>
//sockaddr
//sockaddr_in
//INADDR_ANY

#define BACKLOG 50

void error_handling(char const* msg);

int main(int argc,char* argv[]){

    if(2!=argc){
        printf("Usage: %s <port>\n",argv[0]);
        exit(1);
    }

    int serv_sock;
    serv_sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(-1==serv_sock){
        error_handling("socket() error!");
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(-1==bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))){
        error_handling("bind() error!");
    }

    if(-1==listen(serv_sock,BACKLOG)){
        error_handling("listen() error!");
    }

    int client_sock;
    struct sockaddr_in client_addr;
    socklen_t client_addrlen=sizeof(client_addr);

    printf("Server started on port %s\n",argv[1]);

    while(1){
        client_sock=accept(
            serv_sock
            ,(struct sockaddr*)&client_addr
            ,&client_addrlen
        );
        if(-1==client_sock){
            error_handling("accept() error!");
        }
        //打印客户端地址信息
        //TODO
        close(client_sock);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char const* msg){
    puts(msg);
    putc('\n',stdout);
    exit(1);
}

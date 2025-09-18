#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>

void ErrorHandling(char* message);

int main(int argc,char* argv[]){

    if(argc!=2){
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }

    WSADATA wsaData;

    //初始化套接字库
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0){
        ErrorHandling("WSAStartup() error!");
    }

    SOCKET hServSock;

    //创建套接字
    hServSock=socket(PF_INET,SOCK_STREAM,0);
    if(hServSock==INVALID_SOCKET){
        ErrorHandling("socket() error!");
    }

    SOCKADDR_IN servAddr;
    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAddr.sin_port=htons(atoi(argv[1]));

    //给套接字分配IP地址和端口号
    if(bind(hServSock,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR){
        ErrorHandling("bind() error!");
    }

    //设置套接字为可接收连接请求状态(服务器端套接字)
    if(listen(hServSock,5)==SOCKET_ERROR){
        ErrorHandling("listen() error!");
    }

    SOCKET hClntSock;
    SOCKADDR_IN clntAddr;
    int szClntAddr;
    szClntAddr=sizeof(clntAddr);

    //受理客户端连接请求
    hClntSock=accept(hServSock,(SOCKADDR*)&clntAddr,&szClntAddr);
    if(hClntSock==INVALID_SOCKET){
        ErrorHandling("accept() error");
    }

    char message[]="Hello World!";
    send(hClntSock,message,sizeof(message),0);

    closesocket(hClntSock);
    closesocket(hServSock);

    //注销已经初始化的套接字库
    WSACleanup();
    return 0;
}
void ErrorHandling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

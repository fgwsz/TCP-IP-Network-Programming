#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>

void ErrorHandling(char* message);

int main(int argc,char* argv[]){

    if(argc!=3){
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }

    WSADATA wsaData;

    //初始化Winsock库
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0){
        ErrorHandling("WSAStartup() error!");
    }

    SOCKET hSocket;

    //创建套接字
    hSocket=socket(PF_INET,SOCK_STREAM,0);
    if(hSocket=INVAILD_SOCKET){
        ErrorHandling("socket() error");
    }

    SOCKADDR_IN servAddr;
    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr(argv[1]);
    servAddr.sin_port=htons(atoi(argv[2]));

    //通过此套接字向服务器端发出连接请求
    if(connect(hSocket,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR){
        ErrorHandling("connect() error!");
    }

    char message[30];
    int strlen;

    //接收服务器发来的数据
    strlen=recv(hSocket,message,sizeof(message)-1,0);
    if(strlen==-1){
        ErrorHandling("read() error!");
    }
    printf("Message from server: %s \n",message);

    closesocket(hSocket);

    //注销已初始化的Winsock库
    WSACleanup();
    return 0;
}
void ErrorHandling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}


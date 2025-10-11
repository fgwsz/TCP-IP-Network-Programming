#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>

#define BUF_SIZE 128

void ErrorHandling(char* message);

int main(int argc,char* argv[]){

    if(argc!=3){
        printf("Usage : %s <IP> <port>\n",argv[0]);
        exit(1);
    }

    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0){
        ErrorHandling("WSAStartup() error!");
    }

    SOCKET hSocket;
    hSocket=socket(PF_INET,SOCK_STREAM,0);
    if(hSocket==INVALID_SOCKET){
        ErrorHandling("socket() error");
    }

    SOCKADDR_IN servAddr;
    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr(argv[1]);
    servAddr.sin_port=htons(atoi(argv[2]));

    if(connect(hSocket,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR){
        ErrorHandling("connect() error!");
    }

    int count;
    for(count=0;count<3000;count++){
        printf("Wait time %d \n",count);
    }

    char message[BUF_SIZE];
    int readLen=0;
    readLen=recv(hSocket,message,sizeof(message),0);
    if(readLen==-1){
        ErrorHandling("read() error!");
    }
    printf("Message from server: %s \n",message);

    closesocket(hSocket);
    WSACleanup();
    return 0;
}

void ErrorHandling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

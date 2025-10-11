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
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0){
        ErrorHandling("WSAStartup() error!");
    }

    SOCKET hServSock;
    hServSock=socket(PF_INET,SOCK_STREAM,0);
    if(hServSock==INVALID_SOCKET){
        ErrorHandling("socket() error!");
    }

    SOCKADDR_IN servAddr;
    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAddr.sin_port=htons(atoi(argv[1]));

    if(bind(hServSock,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR){
        ErrorHandling("bind() error!");
    }

    if(listen(hServSock,5)==SOCKET_ERROR){
        ErrorHandling("listen() error!");
    }

    SOCKET hClntSock;
    SOCKADDR_IN clntAddr;
    int szClntAddr;
    szClntAddr=sizeof(clntAddr);

    hClntSock=accept(hServSock,(SOCKADDR*)&clntAddr,&szClntAddr);
    if(hClntSock==INVALID_SOCKET){
        ErrorHandling("accept() error");
    }

    char message[]="Hello World!";
    int idx=0,writeLen=0,strLen=0;
    for(idx=0;idx<sizeof(message);++idx){
        writeLen=send(hClntSock,&message[idx],1,0);
        strLen+=writeLen;
    }
    printf("Function write call count: %d \n",strLen);

    closesocket(hClntSock);
    closesocket(hServSock);

    WSACleanup();
    return 0;
}
void ErrorHandling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

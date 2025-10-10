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
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0){
        ErrorHandling("WSAStartup() error!");
    }

    //创建TCP套接字
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

    char message[30];
    int strLen=0,idx=0,readLen=0;
    //while循环中调用recv函数读取数据,每次1字节
    while(readLen=recv(hSocket,&message[idx++],1,0)){
        if(readLen==-1){
            ErrorHandling("read() error!");
        }
        //每次读取1字节,因此strLen每次加1,这与recv函数调用次数相同
        strLen+=readLen;
    }

    printf("Message from server: %s \n",message);
    printf("Function read call count: %d \n",strLen);

    closesocket(hSocket);
    WSACleanup();
    return 0;
}

void ErrorHandling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

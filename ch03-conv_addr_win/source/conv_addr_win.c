/*
#undef用于取消之前定义的宏.
根据项目环境,VC++会自主声明这2个宏,
在之后调用的转换函数中,参数就将转换为unicode形式,给出错误的运行结果.
所以插入了这2句宏定义
*/
#undef UNICODE
#undef _UNICODE
#include<stdio.h>
#include<winsock2.h>

int main(int argc,char* argv[]){

    char* strAddr="203.211.218.102:9190";
    char strAddrBuf[50];
    SOCKADDR_IN servAddr;
    int size;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);

    size=sizeof(servAddr);
    // 调用WSAStringToAddress函数转换成结构体
    WSAStringToAddress(
        strAddr,AF_INET,NULL,(SOCKADDR*)&servAddr,&size
    );

    size=sizeof(strAddrBuf);
    // 调用WSAAddressToString函数将结构体转换为字符串
    WSAAddressToString(
        (SOCKADDR*)&servAddr,sizeof(servAddr),NULL,strAddrBuf,&size
    );

    printf("Second conv result: %s \n",strAddrBuf);
    WSACleanup();
    return 0;
}

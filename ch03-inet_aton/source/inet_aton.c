#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>

void error_handling(char* message);

int main(int argc,char* argv[]){

    char* addr="127.232.124.79";
    struct sockaddr_in addr_inet;

    if(!inet_aton(addr,&addr_inet.sin_addr)){
        error_handling("Conversion error");
    }else{
        printf("Network ordered integer addr: %#x \n",
            addr_inet.sin_addr.s_addr);
        unsigned char *p=(unsigned char*)&(addr_inet.sin_addr.s_addr);
        printf("字节顺序:%d.%d.%d.%d\n",p[0],p[1],p[2],p[3]);
    }

    return 0;
}

void error_handling(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

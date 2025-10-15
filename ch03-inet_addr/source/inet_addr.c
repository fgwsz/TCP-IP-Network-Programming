#include<stdio.h>
#include<arpa/inet.h>

int main(int argc,char* argv[]){

    char* addr1="1.2.3.4";
    //一个字节能表示的最大无符号正整数是255
    //也就是说下面的地址是一个错误的IP地址
    //由此验证一下inet_addr()的错误检测能力
    char* addr2="1.2.3.256";

    unsigned long conv_addr=inet_addr(addr1);
    if(conv_addr==INADDR_NONE){
        printf("Error occured! \n");
    }else{
        printf("Network ordered integer addr: %#lx \n",conv_addr);
        //可以这样验证字节顺序
        unsigned char *p=(unsigned char*)&conv_addr;
        printf("字节顺序:%d.%d.%d.%d\n",p[0],p[1],p[2],p[3]);
    }

    conv_addr=inet_addr(addr2);
    if(conv_addr==INADDR_NONE){
        printf("Error occured! \n");
    }else{
        printf("Network ordered integer addr: %#lx \n",conv_addr);
        //可以这样验证字节顺序
        unsigned char *p=(unsigned char*)&conv_addr;
        printf("字节顺序:%d.%d.%d.%d\n",p[0],p[1],p[2],p[3]);
    }
    return 0;
}

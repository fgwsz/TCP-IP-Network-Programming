#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc,char* argv[]){

    struct sockaddr_in addr1,addr2;
    addr1.sin_addr.s_addr=htonl(0x1020304);
    addr2.sin_addr.s_addr=htonl(0x1010101);

    char* str_ptr;
    //向inet_ntoa函数传递结构体变量addr1中的IP地址信息并调用该函数
    //返回字符串形式的IP地址
    str_ptr=inet_ntoa(addr1.sin_addr);

    char str_arr[20];
    //复制上面返回的IP地址信息
    strcpy(str_arr,str_ptr);
    printf("Dotted-Decimal notation1: %s \n",str_ptr);

    //再次调用inet_ntoa函数
    //测试此时之前返回的字符串地址是否已经设置了新的IP地址信息
    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2: %s \n",str_ptr);
    printf("Dotted-Decimal notation3: %s \n",str_arr);

    return 0;
}

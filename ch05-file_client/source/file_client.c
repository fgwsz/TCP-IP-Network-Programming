#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char const* message);
int main(int argc,char* argv[]){
    if(argc!=3){
        printf("Usage:%s <IP> <port>\n",argv[0]);
        exit(1);
    }
    int sock=socket(PF_INET,SOCK_STREAM,0);
    if(sock==-1){
        error_handling("socket() error!");
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        error_handling("connect() error!");
    }else{
        puts("Connected..........");
    }
    //读入要下载的服务器文件路径
    char msg_buf[BUF_SIZE];
    memset(&msg_buf[0],0,sizeof(msg_buf));
    printf("Input server file path:\t");
    scanf("%s",msg_buf);
    fgetc(stdin);
    printf("server file path=%s\n",msg_buf);
    //向服务端发送要下载的文件路径
    write(sock,msg_buf,strlen(msg_buf));
    //从服务端读取要下载的文件内容到内存中
    size_t msg_len=read(sock,msg_buf,sizeof(msg_buf));
    if(msg_len==-1){
        //读取失败证明,下载文件路径无效
        error_handling("Server file not found!");
    }else{
        printf("Received %ld bytes.\n",msg_len);
    }
    //读取要下载到的本地路径
    char download_path[BUF_SIZE];
    memset(&download_path[0],0,sizeof(download_path));
    printf("Input download path:\t");
    scanf("%s",download_path);
    fgetc(stdin);
    printf("download path=%s\n",download_path);
    //边读取边写入
    FILE* fp=fopen(download_path,"wb+");
    if(!fp){
        error_handling("fopen(download path) error!");
    }
    fwrite(msg_buf,sizeof(char),msg_len,fp);
    while(read(sock,msg_buf,sizeof(msg_buf))!=-1){
        fwrite(msg_buf,sizeof(char),strlen(msg_buf),fp);
    }
    printf("File downloaded successfully.\n");
    fclose(fp);
    close(sock);
    return 0;
}
void error_handling(char const* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

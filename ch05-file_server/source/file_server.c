#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char const* message);
int main(int argc,char* argv[]){
    if(argc!=2){
        printf("Usage:%s <port>\n",argv[0]);
        exit(1);
    }
    int serv_sock=socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock==-1){
        error_handling("socket() error!");
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        error_handling("bind() error!");
    }
    if(listen(serv_sock,5)==-1){
        error_handling("listen() error!");
    }
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size=sizeof(clnt_addr);
    int clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
    if(clnt_sock==-1){
        error_handling("accept() error!");
    }
    //接收客户端发送来的文件路径
    char file_path[BUF_SIZE];
    memset(&file_path[0],0,sizeof(file_path));
    size_t path_len=read(clnt_sock,file_path,sizeof(file_path));
    if(path_len==-1){
        error_handling("read() error!");
    }
    printf("Message from client:{file path:%s}\n",file_path);
    //检查文件路径是否有效
    FILE* fp=fopen(file_path,"rb");
    if(!fp){
        printf("File{%s} not found!\n",file_path);
        close(clnt_sock);
        close(serv_sock);
        return -1;
    }
    //边读取文件内容,边传递文件内容到客户端
    char buf[BUF_SIZE];
    memset(buf,0,sizeof(buf));
    long long buf_len=0;
    while((buf_len=fread(buf,sizeof(char),sizeof(buf),fp))>0){
        if(write(clnt_sock,buf,buf_len)!=buf_len){
            error_handling("write() error!");
        }
    }
    if(ferror(fp)){
        error_handling("fread() error!");
    }else if(feof(fp)){
        printf("File transfer successfully.\n");
    }
    fclose(fp);
    close(clnt_sock);
    close(serv_sock);
    return 0;
}
void error_handling(char const* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

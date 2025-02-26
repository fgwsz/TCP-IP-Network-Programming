#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30
int main(int argc,char* argv[]){
    int fds[2];
    char str[]="Who are you?";
    char buf[BUF_SIZE];
    pid_t pid;
    pipe(fds);
    pid=fork();
    if(pid==0){//子进程的执行空间
        write(fds[1],str,sizeof(str));//向管道入口的文件描述符写入信息
    }else{//父进程的执行空间
        read(fds[0],buf,BUF_SIZE);//从管道出口的文件描述符读取信息
        puts(buf);
    }
    return 0;
}

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#define BUF_SIZE 30
//parent->child
//chile->parent
//parent->child
void read_childproc(int sig);
int main(int argc,char* argv[]){
    int fds_to_child[2],fds_to_parent[2];
    char str1[]="Who are you?";
    char str2[]="I am child proc, and you?";
    char str3[]="I am parent proc.";
    char buf[BUF_SIZE];
    struct sigaction act;
    int len;
    pipe(fds_to_child),pipe(fds_to_parent);
    act.sa_handler=read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGCHLD,&act,0);
    pid_t child_pid=fork();
    if(child_pid==0){//子进程的执行空间
        pid_t read_pid=fork();
        if(read_pid==0){
            for(int i=0;i<2;++i){
                while((len=read(fds_to_child[0],buf,BUF_SIZE))>0){
                    buf[len]='\0';
                    printf("Child proc recv:%s\n",buf);
                }
            }
        }else{
            write(fds_to_parent[1],str2,sizeof(str2));
            printf("Child proc post:%s\n",str2);
        }
    }else{//父进程的执行空间
        printf("child proc id: %d\n",child_pid);
        pid_t read_pid=fork();
        if(read_pid==0){
            for(int i=0;i<1;++i){
                while((len=read(fds_to_parent[0],buf,BUF_SIZE))>0){
                    buf[len]='\0';
                    printf("Parent proc recv:%s\n",buf);
                }
            }
        }else{
            write(fds_to_child[1],str1,sizeof(str1));
            printf("Parent proc post:%s\n",str1);
            sleep(1);
            write(fds_to_child[1],str3,sizeof(str3));
            printf("Parent proc post:%s\n",str3);
        }
    }
    return 0;
}
void read_childproc(int sig){
    pid_t pid;
    int status;
    pid=waitpid(-1,&status,WNOHANG);
    printf("remove proc id: %d \n",pid);
}

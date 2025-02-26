#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

#define BUF_SIZE 30
char buf[BUF_SIZE];
void keyboard_handling(int sig);
void log_something(int sig);
int main(int argc,char* argv[]){
    struct sigaction act_1,act_2;
    act_1.sa_handler=keyboard_handling;
    act_2.sa_handler=log_something;
    sigemptyset(&act_1.sa_mask);
    sigemptyset(&act_2.sa_mask);
    act_1.sa_flags=0;
    act_2.sa_flags=0;
    sigaction(SIGINT,&act_1,0);
    sigaction(SIGALRM,&act_2,0);
    alarm(1);
    for(int i=0;i<100;++i){
        puts("wait...");
        sleep(10);
    }
    return 0;
}
void keyboard_handling(int sig){
    alarm(0);
    printf("Input message(Y to quit): ");
    memset(buf,0,BUF_SIZE);
    fgets(buf,BUF_SIZE,stdin);
    if(!strcmp(buf,"Y\n")||!strcmp(buf,"y\n")){
        exit(0);
    }
    alarm(1);
}
void log_something(int sig){
    puts("hello!");
    alarm(1);
}

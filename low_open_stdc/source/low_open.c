#include<stdio.h>
#include<stdlib.h>

int main(void){
    FILE* fp=fopen("data.txt","w+");
    if(!fp){
        perror("fopen() error!");
        return 1;
    }
    printf("file pointer: %p \n",fp);
    char buf[]="Let's go!\n";
    size_t size=sizeof(buf);
    size_t count=size/sizeof(buf[0])-1;
    if(fwrite(buf,size,count,fp)<count){
        perror("fwrite() error!");
    }
    fclose(fp);
    return 0;
}

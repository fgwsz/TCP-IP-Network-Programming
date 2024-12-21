#include<stdio.h>
#include<stdlib.h>

#define BUF_SIZE 100

int main(void){
    char buf[BUF_SIZE];
    FILE* fp=fopen("data.txt","r");
    if(!fp){
        perror("fopen() error!");
        return 1;
    }
    printf("file pointer: %p \n",fp);
    if(fread(buf,sizeof(buf[0]),BUF_SIZE,fp)==BUF_SIZE){
        printf("file data: %s",buf);
    }else{
        if(feof(fp)){
            printf("file data: %s",buf);
        }else if(ferror(fp)){
            perror("fread() error!");
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

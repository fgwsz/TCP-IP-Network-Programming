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
    if(fprintf(fp,"%s",buf)<0){
        perror("fprintf() error!");
    }
    fclose(fp);
    return 0;
}

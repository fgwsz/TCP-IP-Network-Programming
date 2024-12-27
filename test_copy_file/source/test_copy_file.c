#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_SIZE 1024
int copy_file(char const* from_file_path,char const* to_file_path){
    FILE* from_fp=NULL;
    FILE* to_fp=NULL;
    size_t file_size=0;
    size_t count=0;
    char buf[BUF_SIZE];
    memset(buf,0,BUF_SIZE);

    from_fp=fopen(from_file_path,"rb");
    if(!from_fp){
        perror("fopen(from file paht) error!");
        return -1;
    }
    to_fp=fopen(to_file_path,"wb+");
    if(!to_fp){
        perror("fopen(to file path) error!");
        return -1;
    }
    //获取from_file_path的文件大小
    //分次来先读取到buf,然后转到to_file_path中
    while((count=fread(buf,sizeof(char),BUF_SIZE,from_fp))>0){
        fwrite(buf,sizeof(char),count,to_fp);
    } 
    //检查是否是因为遇到EOF结束循环还是发生错误导致退出
    if(feof(from_fp)){
        puts("\nFile copied successfully.");
    }else{
        perror("Error reading source file.");
    }
    fclose(to_fp);
    fclose(from_fp);
    return 0;
}
int main(int argc,char* argv[]){
    char from_filename[BUF_SIZE];
    char to_filename[BUF_SIZE];
    memset(from_filename,0,BUF_SIZE);
    memset(to_filename,0,BUF_SIZE);
    printf("Input from file path:\t");
    scanf("%s",from_filename);
    fgetc(stdin);
    printf("Input to file path:\t");
    scanf("%s",to_filename);
    fgetc(stdin);
    return copy_file(from_filename,to_filename);
}

#include<stdio.h>
#include<stdlib.h>
int copy_file(char const* from_file_path,char const* to_file_path){
    FILE* from_fp,*to_fp;
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
    fclose(to_fp);
    fclose(from_fp);
    return 0;
}
int main(int argc,char* argv[]){
    
    printf("Input from file path:\t");
    char ch;
    while(fgets(ch,1,stdin)!=NULL&&ch!='\n'){
        
    }
    scanf("%s\n","")
    return 0;
}

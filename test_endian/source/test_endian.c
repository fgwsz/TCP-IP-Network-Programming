#include<stdio.h>
struct Person{
    int age_;
    char name_[4];
};
union TestPersonEndian{
    struct Person person_;
    unsigned char byte_array_[sizeof(struct Person)];
};
int main(int argc,char* argv[]){
    union TestPersonEndian test;
    test.person_.age_=0x11223344;
    test.person_.name_[0]=0x54;
    test.person_.name_[1]=0x6f;
    test.person_.name_[2]=0x6d;
    test.person_.name_[3]='\0';
    int index;
    for(index=0;index<sizeof(test.byte_array_);++index){
        printf(
            "%p:%p\n"
            ,&(test.byte_array_[index])
            ,(void*)(test.byte_array_[index])
        );
    }
    return 0;
}

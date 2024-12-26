#include<stdlib.h>//malloc free
#include<string.h>//memset

#include"String.h"

#define __STRING_DEFAULT_CAPACITY 10

static void* __memory_alloc(size_t size){
    void* result=NULL;
    while(1){
        result=malloc(size);
        if(result!=NULL){
            break;
        }
    }
    memset(result,0,size);
    return result;
}
static void __memory_free(void* pointer){
    if(pointer!=NULL){
        free(pointer);
    }
}
struct String{
    size_t capacity_;
    size_t size_;
    char* data_;
};
struct String* String_ctor(void){
    struct String* result=(struct String*)
        __memory_alloc(sizeof(struct String));
    result->capacity_=__STRING_DEFAULT_CAPACITY;
    result->size_=1;//'\0'
    result->data_=(char*)__memory_alloc(sizeof(char)*(this->capacity_));
    return result;
}
bool String_empty(struct String* self){
    return String_length(self)==0;
}
bool String_clear(struct String* self){
    if(self!=NULL){
        self->data_[0]='\0';
        self->size_=1;
        return true;
    }
    return false;
}
bool String_set_c_str(struct String* self,char const* c_str){
    if(self==NULL){
        return false;
    }
    if(c_str==NULL||length==0){
        String_clear(self);
        return true;
    }
    if((c_str>=this->data_)&&(c_str<(this->data_+this->capacity_))){
        if((c_str+length+1)>(this->data_+this->capacity_)){
            return false;
        }else{
            memmove(this->data_,c_str,length);
            self->data_[length]='\0';
            self->size_=length+1;
            return true;
        }
    }
    if(length+1>this->capacity_){
        __memory_free(this->data_);
        size_t new_capacity=this->capacity_*2;
        self->data_=(char*)__memory_alloc(new_capacity);
        self->capacity_=new_capacity;
    }
    memmove(this->data_,c_str,length);
    self->data_[length]='\0';
    self->size_=length+1;
    return true;
}
bool String_set_string(struct String* self,struct String const* string){
    if(self!=string){
        return String_set_c_str(
            self
            ,String_get_const_c_str(string)
            ,String_length(string)
        );
    }
    return self!=NULL;
}
char* String_get_c_str(struct String* self){
    if(self!=NULL){
        return self->data_;
    }
    return NULL;
}
char const* String_get_const_c_str(struct String const* self){
    if(self!=NULL){
        return self->data_;
    }
    return NULL;
}
size_t String_length(struct String const* self){
    if(self!=NULL){
        return self->size_-1;
    }
    return 0;
}
int String_compare(struct String const* self,struct String const* rhs){
    //TODO
}
bool String_swap(struct String* self,struct String* rhs){
    //TODO
}
bool String_append(struct String* self,struct String const* rhs){
    //TODO
}
struct String* String_concat(struct String const* lhs,struct String const* rhs){
    //TODO
}
void String_dtor(struct String* self){
    if(self!=NULL){
        __memory_free(self->data_);
        __memory_free(self);
    }
}

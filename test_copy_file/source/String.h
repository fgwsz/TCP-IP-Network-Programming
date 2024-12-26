#ifndef __STRING_H__
#define __STRING_H__
#include<stddef.h>//size_t
#include<stdbool.h>//bool true false
struct String;
extern struct String* String_ctor(void);
extern bool String_empty(struct String* self);
extern bool String_clear(struct String* self);
// 如果c_str是NULL或者length为0,String会置空
extern bool String_set_c_str(struct String* self,char const* c_str,size_t length);
extern bool String_set_string(struct String* self,struct String const* string);
extern char* String_get_c_str(struct String* self);
extern char const* String_get_const_c_str(struct String const* self);
extern size_t String_length(struct String const* self);
extern int String_compare(struct String const* self,struct String const* rhs);
extern bool String_swap(struct String* self,struct String* rhs);
extern bool String_append(struct String* self,struct String const* rhs);
extern struct String* String_concat(struct String const* lhs,struct String const* rhs);
extern void String_dtor(struct String* self);
#endif//__STRING_H__

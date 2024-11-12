#include "../include/string.h"
int strlen(const char* str){
    char c = str[0];
    int i = 0; 
    while (c != '\0')
    {
        i++;
        c = str[i];
    }
    return i;
    
}

int memcmp(const void* v1,const void* v2, size_t s){
    char* _v1, _v2;
    _v1 = (char*)v1;
    _v2 = (char*)v2;
    for(size_t i = 0; i < s; i++){
        if( _v1 + i == _v2 + i){
            continue;
        }
        else{
            return (sizeof(_v1) - sizeof(_v2));
        }
    }
}

void* memcpy(void* __restrict var1, const void* __restrict var2, size_t s){
    
}

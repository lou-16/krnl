#include "../include/stdlib.h"

void abort()
{
    
    //SIGABRT signal invoked
    printf("Abort Called\n");

    while(1) {}
    __builtin_unreachable();

}


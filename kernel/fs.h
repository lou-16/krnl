#ifndef fs_h
#define fs_h

#include <stdint.h>
/*
    UNIX used file descriptors to see what exactly is open. so lets make some file descriptors. for 0
    we have stdin, for 1 we have stdout and 2 is stderr. once we get these 3 working we'll actually 
    implement proper fs interactions. but before, i lowkey js realised there needs to be a memory syscall

    syscall list :
    open
    read
    write
    close
*/




#endif
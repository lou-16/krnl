#ifndef _STRING_H
#define _STRING_H 1

#include <sys/cdefs.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    int printf(const char* __restrict, ...);
    int putchar(int);
    int puts(const char*);

#ifdef __cplusplus
}
#endif

#endif /*END STDIO.H*/
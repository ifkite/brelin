#ifndef _dbg_h_
#define _dbg_h_
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define Debug(M, ...) fprintf(stderr, "Debug %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define check(A, M, ...) if((!A)) {log_err(M, ##__VA_ARGS__);errno = 0;goto error;}
#define log_err(M, ...) fprintf(stderr, "(Error %s:%d %s)" M "\n" __FILE__, __LINE__, clean_err())
#define clean_err() (errno = 0 ? "None" : strerror(error))
#endif

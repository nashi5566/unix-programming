#ifndef _SANDBOX_H
#define _SANDBOX_H

void* __func_hook(const char* symbol);
int check_access(const char* pathname, char* arg);
int check_creat(const char* path, char* symbol);

#endif

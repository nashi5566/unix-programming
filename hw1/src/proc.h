#ifndef __PROC_H
#define __PROC_H

#define _MAX_LENGTH 1024

#include "list.h"
#include "connect.h"

typedef struct proc proc;
struct proc{
	char *pid;
	node *i;
	char cmdline[_MAX_LENGTH];
	char processName[_MAX_LENGTH];
};

list *addPID();
void addInode(list* lHead, char* pid);
void addCMD(list* lHead, char* pid);
void addName(list* lHead, char* pid);
node *inodeSearch(node* nHead, long inode);
char *split(char* string, int base, int tail);

#endif

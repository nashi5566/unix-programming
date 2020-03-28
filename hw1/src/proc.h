#ifndef __PROC_H
#define __PROC_H

#define _MAX_LENGTH 1024

//#include "list.h"
//#include "connect.h"

struct node;
struct list;

typedef struct proc proc;
struct proc{
	char *pid;
	struct node *i;
	char cmdline[_MAX_LENGTH];
	char processName[_MAX_LENGTH];
};

struct list *addPID();
void addInode(struct list* lHead, char* pid);
void addCMD(struct list* lHead, char* pid);
void addName(struct list* lHead, char* pid);
struct node *inodeSearch(struct node* nHead, long inode);
char *split(char* string, int base, int tail);

#endif

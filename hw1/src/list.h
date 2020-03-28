#ifndef __LIST_H
#define __LIST_H

//#include "connect.h"
//#include "proc.h"

typedef struct list list;
struct list{
	struct list *lNext;
// DATA ENTRY
	struct proc *process;
};

typedef struct node node;
struct node{
	long inode;
	int fd;
	struct node *nNext;
};

struct list *newList();
struct list *append(struct list *l);
struct list *searchName(struct list *lHead, char* name);
struct list *searchPID(struct list *lHead, char* pid);
struct node *nodeAppend(struct node *n);
struct node *newNode();

#endif

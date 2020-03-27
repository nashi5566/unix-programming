#ifndef __LIST_H
#define __LIST_H

#include "connect.h"
#include "proc.h"

typedef struct list list;
struct list{
	struct _LIST_ENTRY *lNext;
// DATA ENTRY
	struct __PROC_ENTRY *process;
};

typedef struct clist clist;
struct clist{
	struct __CONNECT_LIST *lNext;
	struct __CONECT_ENTRY *connect;
};

typedef struct node node;
struct node{
	long inode;
	int fd;
	struct __NODE_LIST *nNext;
};

list *newList();
list *append(list *l);
list *searchName(list *lHead, char* name);
list *searchPID(list *lHead, char* pid);
node *nodeAppend(node *n);
node *newNode();

#endif

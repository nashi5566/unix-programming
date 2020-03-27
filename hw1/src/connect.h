#ifndef __CONNECT_H
#define __CONNECT_H

#include "list.h"
#include "proc.h"

typedef struct connect connect;
struct connect{
	char type[20];
	long local_port;
	long fore_port;
	char local[100];
	char foregin[100];
	char protocol[100];
	long inode;
};

char *ip4(char* address);
char *ip6(char* address);
connect *inodeSearch(clist* cHead, long inode);
clist *cappend(clist* c);
clist *newCList();
void parse(char* path, char* type, clist *c);
#endif

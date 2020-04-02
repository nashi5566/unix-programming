#ifndef __PROC_H
#define __PROC_H

struct list;

typedef struct process{
	char name[1024];
	char cmdline[1024];
	long pid;
	struct list *fdlist;
} process;

typedef struct inode{
	long pid;
	char inode_num[60];
} inode;

list *findallpid(list *l);
node *pidfindprocess(list *l, long pid);
void addCMD(list *l, long pid);
void addName(list *l, long pid);
list *findsocketinode(list* inodelist, long pid);
//process *findcmdline(process* pHead, long pid);
//process *findname(process* pHead, char name[]);
//process *collectinode(process* pHead, struct *inode);

#endif

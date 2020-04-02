#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<getopt.h>
#include<string.h>

#include "list.h"
#include "proc.h"

#define TCP "/proc/net/tcp"
#define UDP "/proc/net/udp"
#define TCP6 "/proc/net/tcp6"
#define UDP6 "/proc/net/udp6"

int main(int argc, char** argv){
	list *l = (list*)malloc(sizeof(list)); 
	l = findallpid(l);
	//addCMD(l, "29824");
	list* i = (list*)malloc(sizeof(list));
	i->lHead = NULL;
	while(l->lHead != NULL){
		i = findsocketinode(l, ((process*)l->lHead->data)->pid);

		l->lHead = l->lHead->next;
	}

}


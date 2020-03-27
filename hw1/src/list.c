#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "proc.h"
#include "list.h"

list *newList(){
	list *l = (list *)malloc(sizeof(list));
	l->process = (proc *)malloc(sizeof(proc));
	l->process->i= newNode();
	return l;
}

node *newNode(){
	node *n = (node*)malloc(sizeof(node));
	return n;
}

node *nodeAppend(node *n){
	n->nNext = newNode();
	n = n->nNext;
	n->nNext = NULL;

	return n;
}

list *searchPID(list *lHead, char *pid){
	while(lHead != NULL){
		if(!strcmp(lHead->process->pid, pid)){
			return lHead;
		}
		else lHead = lHead->lNext;
	}

	puts("The input PID is not in the list.\n");
	return NULL;
}

list *searchName(list *lHead, char *name){
	while(lHead != NULL){
		if(!strcmp(lHead->process->processName, name)){
			return lHead;
		}
		else lHead = lHead->lNext;
	}

	puts("The input process is not in the list.\n");
	return NULL;
}

list *append(list *l){
	l->lNext = newList();
	l = l->lNext;
	l->lNext = NULL;

	return l;
}
